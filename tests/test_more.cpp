////
//// Created by Darwin Yuan on 2020/8/30.
////

#include <holo/holo.h>
#include <catch.hpp>
#include <optional>

enum class node_category {
   Root,
   Intermediate,
   Leaf
};

template <typename T, node_category CATEGORY>
struct node_trait {
   using node_type = T;
   constexpr static node_category category = CATEGORY;
};

#define USING_TL 1

#if USING_TL
#define make_tuple_h make_type_list
#define make_pair_h  make_type_pair
#define tuple_t_h    type_list_t
#else
#define make_tuple_h make_tuple
#define make_pair_h  make_pair
#define tuple_t_h    tuple_t
#endif

template<typename NODE, typename = void>
struct down_stream_trait;

struct node_signature {};

template <typename NODE>
struct down_stream_node_ref {
   constexpr static auto node_list = holo::tuple_t_h<NODE>;
};


//////////////////////////////////////////////////////////////////////////////
template<typename COND, typename NODE_LIKE>
struct down_stream_maybe {
   using decorated_node = typename down_stream_trait<NODE_LIKE>::type;
   constexpr static auto node_list = decorated_node::node_list;
};

template<typename COND, typename NODE_LIKE>
struct down_stream_trait<down_stream_maybe<COND, NODE_LIKE>, void> {
   using type = down_stream_maybe<COND, NODE_LIKE>;
};

template<typename ... NODEs_LIKE>
struct down_stream_fork {
   constexpr static auto node_list =
      holo::make_tuple_h(down_stream_trait<NODEs_LIKE>::type::node_list...)
      | holo::flatten();
};

template<typename ... NODEs_LIKE>
struct down_stream_trait<down_stream_fork<NODEs_LIKE...>, void> {
   using type = down_stream_fork<NODEs_LIKE...>;
};


template<typename NODE>
struct down_stream_trait<NODE, std::enable_if_t<std::is_base_of_v<node_signature, NODE>>> {
   using type = down_stream_node_ref<NODE>;
};


template<typename COND, typename NODE_LIKE_1, typename NODE_LIKE_2>
struct down_stream_either {
   using decorated_node_1 = typename down_stream_trait<NODE_LIKE_1>::type;
   using decorated_node_2 = typename down_stream_trait<NODE_LIKE_2>::type;

   constexpr static auto node_list = \
      holo::concat( down_stream_trait<NODE_LIKE_1>::type::node_list
      , down_stream_trait<NODE_LIKE_2>::type::node_list);
};

template<typename COND, typename NODE_LIKE_1, typename NODE_LIKE_2>
struct down_stream_trait<down_stream_either<COND, NODE_LIKE_1, NODE_LIKE_2>, void> {
   using type = down_stream_either<COND, NODE_LIKE_1, NODE_LIKE_2>;
};

template<typename T>
struct graph_port;

template<typename PORT, typename NODE_LIKE>
struct graph_port<auto (PORT) -> NODE_LIKE> final {
   using node_like_type = typename down_stream_trait<NODE_LIKE>::type;
   constexpr static auto node_list = node_like_type::node_list;
};

struct root_signature {};

template<typename NODE, typename ... PORTS>
struct graph_node final {
   constexpr static auto is_root = holo::bool_c<std::is_base_of_v<root_signature, NODE>>;
   using node_type = NODE;
   constexpr static auto direct_decedents =
      holo::make_tuple_h(graph_port<PORTS>::node_list...)
      | holo::flatten()
      | holo::unique();
};

template<typename ... NODES>
struct sub_graph_analyzer final {
   constexpr static auto nodes_map = holo::make_tuple_h(
      holo::make_pair_h(holo::type_c<typename NODES::node_type>, NODES::direct_decedents)...);

   template<typename T>
   constexpr static auto get_all_decedents(T list) {
      return holo::fold_left(holo::make_tuple_h(), [](auto acc, auto elem) {
         auto entry = holo::find_if([=](auto v){ return holo::first(v) == elem; }, nodes_map);
         if constexpr(holo::is_nothing(entry)) {
            return holo::append(elem, acc);
         } else {
            return holo::concat(acc, holo::append(elem, get_all_decedents(holo::second(entry))));
         }
      }, list);
   }

   constexpr static auto all_decedents_map =
      nodes_map
      | holo::transform([](auto elem) {
            return holo::make_pair_h(holo::first(elem), holo::unique(get_all_decedents(holo::second(elem))));
         });


   constexpr static auto sorted_non_leaf_nodes =
      all_decedents_map
      | holo::sort([](auto l, auto r) {
         return holo::contains(holo::first(l), holo::second(r)); })
      | holo::transform([](auto elem) {
         return holo::first(elem); })
      | holo::reverse();


   constexpr static auto root_nodes =
      holo::tuple_t<NODES...>
      | holo::filter([](auto elem){
         return decltype(elem)::type::is_root == holo::bool_c<true>; })
      | holo::transform([](auto elem){
         return holo::type_c<typename decltype(elem)::type::node_type>;
      });


   constexpr static auto sorted_tagged_intermediate_nodes =
      sorted_non_leaf_nodes
      | holo::remove_if([](auto elem) {
         return holo::contains(elem, root_nodes); })
      | holo::transform([](auto elem) {
         return holo::type_c<node_trait<typename decltype(elem)::type, node_category::Intermediate>>;
      });


   constexpr static auto leaf_tagged_nodes =
      all_decedents_map
      | holo::fold_left(holo::make_tuple_h(), [](auto acc, auto elem){
         return holo::concat(acc, holo::second(elem)); })
      | holo::unique()
      | holo::remove_if([](auto elem) {
         return holo::contains(elem, sorted_non_leaf_nodes); })
      | holo::transform([](auto elem) {
         return holo::type_c<node_trait<typename decltype(elem)::type, node_category::Leaf>>;
      });

public:
   constexpr static auto all_sorted_sub_graph_nodes = holo::concat(sorted_tagged_intermediate_nodes, leaf_tagged_nodes);
   constexpr static auto sorted_nodes_desc =
      sorted_non_leaf_nodes
      | holo::transform([](auto elem){
         constexpr auto entry = holo::tuple_t<NODES...>
                                | holo::find_if([=](auto v){
            return holo::type_c<typename decltype(v)::type::node_type> == elem; });

         static_assert(!holo::is_nothing(entry));
         return entry;
      });
};


struct root_1 : root_signature{
   constexpr static auto root_id = 0;
};

struct root_2 : root_signature{
   constexpr static auto root_id = 1;
};

struct node_3 : node_signature{
   constexpr static auto id = 3;
};

struct node_4 : node_signature{
   constexpr static auto id = 4;
};



struct node_5 : node_signature{
   constexpr static auto id = 5;
};
struct node_6 : node_signature{
   constexpr static auto id = 6;
};
struct node_7 : node_signature{
   constexpr static auto id = 7;
};
struct node_8 : node_signature{
   constexpr static auto id = 8;
};

struct port_1 {
};
struct port_2 {
};
struct port_3 {
};
struct port_4 {
};
struct port_5 {
};
struct port_6 {
};
struct port_7 {
};
struct port_8 {
};
struct port_9 {
};

struct cond_1 {
};

struct cond_2 {
};

using root_graph1 =
graph_node<root_1,
      auto (port_1) -> node_8,
      auto (port_2) -> down_stream_maybe<cond_2, node_3>,
      auto (port_3) -> down_stream_either<cond_1, node_8, node_3>,
      auto (port_4) -> down_stream_fork<node_5, node_4, down_stream_maybe<cond_2, node_8>>>;

using root_graph2 =
   graph_node<root_2,
      auto (port_1) -> node_7>;

using root_graph3 =
   graph_node<node_5,
      auto (port_5) -> node_8,
      auto (port_6) -> down_stream_fork<node_4, down_stream_maybe<cond_2, node_3>>>;

using root_graph4 =
   graph_node<node_3,
      auto (port_7) -> node_4,
      auto (port_8) -> down_stream_fork<node_8, node_6>,
      auto (port_9) -> node_7>;

namespace {

   template<typename T> struct S;
   struct U{};
   struct V{bool c;};
   TEST_CASE("test transition") {
      using sub = sub_graph_analyzer<root_graph1, root_graph2, root_graph3, root_graph4>;
      static_assert(holo::contains(holo::type_c<double>, holo::tuple_t<long, int, double>));
      static_assert(!holo::contains(holo::type_c<char>, holo::tuple_t<long, int, double>));
      static_assert(!holo::Is_True_V<decltype(holo::contains(holo::type_c<char>, holo::tuple_t<long, int, double>))>);
      static_assert(holo::Is_True_V<decltype(holo::contains(holo::type_c<double>, holo::tuple_t<long, int, double>))>);

//      auto v = holo::Is_True_V<decltype(holo::contains(holo::type_c<double>, holo::tuple_t<long, int, double>))>;
//      S<decltype(v)> ss;

      S<decltype(sub::leaf_tagged_nodes)> s;
   }
}

