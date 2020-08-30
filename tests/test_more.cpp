////
//// Created by Darwin Yuan on 2020/8/30.
////
//
//#include <holo/holo.h>
//#include <catch.hpp>
//#include <optional>
//
//struct device_info {
//   const uint8_t device_id;
//   const bool is_preview;
//
//   inline constexpr auto tie() const noexcept {
//      return std::tie(device_id, is_preview);
//   }
//};
//
//inline constexpr auto operator==(device_info const& lhs, device_info const& rhs) noexcept -> bool {
//   return lhs.tie() == rhs.tie();
//}
//
//inline constexpr auto operator!=(device_info const& lhs, device_info const& rhs) noexcept -> bool {
//   return !operator==(lhs, rhs);
//}
//
//inline constexpr auto operator<(device_info const& lhs, device_info const& rhs) noexcept -> bool {
//   return lhs.tie() < rhs.tie();
//}
//
//inline constexpr auto operator<=(device_info const& lhs, device_info const& rhs) noexcept -> bool {
//   return lhs.tie() <= rhs.tie();
//}
//
//inline constexpr auto operator>(device_info const& lhs, device_info const& rhs) noexcept -> bool {
//   return lhs.tie() > rhs.tie();
//}
//
//inline constexpr auto operator>=(device_info const& lhs, device_info const& rhs) noexcept -> bool {
//   return lhs.tie() >= rhs.tie();
//}
//
//
//struct root_state {
//   device_info const* device_info_{};
//   size_t size_{};
//
//   constexpr auto get_device_info(uint8_t device_id) const -> struct device_info const* {
//      for(size_t i=0; i < size_; i++) {
//         if(device_info_[i].device_id == device_id) {
//            return device_info_ + i;
//         }
//      }
//      return nullptr;
//   }
//
//   auto cleanup() {
//      device_info_ = nullptr;
//      size_ = 0;
//   }
//};
//
//inline constexpr auto operator==(root_state const& lhs, root_state const& rhs) noexcept -> bool {
//   if(lhs.size_ != rhs.size_) return false;
//   for(size_t i=0; i<lhs.size_; i++) {
//      if(lhs.device_info_[i] != rhs.device_info_[i]) return false;
//   }
//   return true;
//}
//
//inline constexpr auto operator!=(root_state const& lhs, root_state const& rhs) noexcept -> bool {
//   return !operator==(lhs, rhs);
//}
//
//
/////////////////////////////////////////////////////////////////////////////////
//template<typename DEVICE>
//struct preview_tag {
//   constexpr static auto Device_Id = DEVICE::Device_Id;
//   constexpr static auto Is_Preview = true;
//};
//
//namespace detail {
//   template<typename DEVICE, typename = void>
//   struct device_trait {
//      constexpr static auto Device_Id = DEVICE::Device_Id;
//      constexpr static auto Is_Preview = false;
//   };
//
//   template<typename DEVICE>
//   struct device_trait<DEVICE, std::enable_if_t<DEVICE::Is_Preview>> : DEVICE {};
//}
//
/////////////////////////////////////////////////////////////////////////////////
//template<typename ... DEVICEs>
//struct device_state {
//   constexpr static size_t Num_Of_Devices = sizeof...(DEVICEs);
//   constexpr static auto Sorted_Devices =
//      holo::sort([](auto l, auto r) {
//         return holo::char_c<decltype(l)::type::Device_Id>
//                <
//                holo::char_c<decltype(r)::type::Device_Id>;
//      }, holo::tuple_t<detail::device_trait<DEVICEs>...>);
//
//   template<typename ... Ts>
//   struct devices_type {
//      constexpr static device_info Devices[] = {
//         {Ts::Device_Id, Ts::Is_Preview}...
//      };
//      constexpr static root_state Root_State { .device_info_ = Devices, .size_ = Num_Of_Devices };
//   };
//
//   using devices = holo::tuple_trait_t<decltype(Sorted_Devices), devices_type>;
//   constexpr static auto Devices = devices::Devices;
//
//   constexpr static auto Root_State = devices::Root_State;
//
//   template<typename DEVICE>
//   inline static constexpr auto content_equal() -> bool {
//      for(size_t i=0; i<Num_Of_Devices; i++) {
//         if (Devices[i] != DEVICE::Devices[i]) {
//            return false;
//         }
//      }
//      return true;
//   }
//
//   template<typename DEVICE>
//   inline static constexpr auto equals() noexcept {
//      if constexpr (Num_Of_Devices != DEVICE::Num_Of_Devices) {
//         return holo::bool_c<false>;
//      } else {
//         if constexpr (content_equal<DEVICE>()) {
//            return holo::bool_c<true>;
//         } else {
//            return holo::bool_c<false>;
//         }
//      }
//   }
//
//   template<typename DEVICE>
//   inline static constexpr auto content_less_than() -> bool {
//      for(size_t i=0; i<Num_Of_Devices; i++) {
//         if (Devices[i] >= DEVICE::Devices[i]) {
//            return false;
//         }
//      }
//      return true;
//   }
//
//   template<typename DEVICE>
//   inline static constexpr auto less_than() noexcept {
//      if constexpr (Num_Of_Devices < DEVICE::Num_Of_Devices) {
//         return holo::bool_c<true>;
//      } else if constexpr(Num_Of_Devices > DEVICE::Num_Of_Devices) {
//         return holo::bool_c<false>;
//      } else {
//         if constexpr (content_less_than<DEVICE>()) {
//            return holo::bool_c<true>;
//         } else {
//            return holo::bool_c<false>;
//         }
//      }
//   }
//};
//
//#define __g_PREVIEW(device)     preview_tag<device>
//#define __g_STATE(...)          std::decay_t<decltype(std::declval<device_state<__VA_ARGS__>>())>
//
//template<typename T> struct S;
//
//class state_transition_algo {
//   template<typename FROM, typename TARGET, typename REST, typename TRANSITIONS>
//   constexpr static auto
//   search_next_layer(FROM const &from, TARGET const &target, TRANSITIONS const &transitions, REST const &rest) {
//      auto all_non_empty_paths = transitions
//         | holo::transform([&](auto elem) {
//              auto result = find_shortcut(holo::second(elem), target, rest);
//              static_assert(holo::Is_Tuple_v<decltype(result)>);
//              return result; })
//         | holo::remove_if([](auto elem) {
//              return holo::length(elem) == holo::size_c<0>; });
//
//      if constexpr (holo::length(all_non_empty_paths) == holo::size_c<0>) {
//         return holo::make_tuple();
//      } else if constexpr (holo::length(all_non_empty_paths) == holo::size_c<1>) {
//         return holo::prepend(from, holo::head(all_non_empty_paths));
//      } else {
//         S<decltype(all_non_empty_paths)> s;
//         return all_non_empty_paths
//                | holo::sort([](auto l, auto r) { return holo::length(l) < holo::length(r); })
//                | holo::head()
//                | holo::prepend(from);
//      }
//   }
//
//   template<typename FROM, typename TARGET, typename REST, typename TRANSITIONS>
//   constexpr static auto
//   find_shortcut_(FROM const &from, TARGET const &target, TRANSITIONS const& direct_transition, REST const &rest) {
//      auto result = direct_transition
//         | holo::find_if([&](auto elem) {
//            using to = typename std::decay_t<decltype(holo::second(elem))>::type;
//            return std::decay_t<decltype(target)>::type::template equals<to>(); });
//
//      if constexpr (!holo::is_nothing(result)) {
//         // we got the shortcut
//         return holo::make_tuple(from, holo::second(result));
//      } else {
//         return search_next_layer(from, target, direct_transition, rest);
//      }
//   }
//
//public:
//   template<typename FROM, typename TARGET, typename REST>
//   constexpr static auto find_shortcut(FROM const& from, TARGET const& target, REST const& rest) {
//      auto parts = rest | holo::partition([&](auto elem) {
//         using from_type = typename std::decay_t<decltype(from)>::type;
//         return std::decay_t<decltype(holo::first(elem))>::type::template equals<from_type>();
//      });
//
//      if constexpr (holo::Is_True_V<decltype(holo::length(holo::first(parts)) == holo::size_c<0>)>) {
//         return holo::tuple_t<>;
//      } else {
//         return find_shortcut_(from, target, holo::first(parts), holo::second(parts));
//      }
//   }
//
//   template<typename TRANS_PAIR, typename REST>
//   constexpr static auto find_shortcut(TRANS_PAIR const& trans, REST const& rest) {
//      return find_shortcut(holo::first(trans), holo::second(trans), rest);
//   }
//};
//
//template<typename ... Ts> struct transition_trait;
//
//template<typename FROM, typename TO1, typename ... TOs>
//struct transition_trait<auto (FROM) -> TO1, TOs...> {
//   using from_state = FROM;
//   using to_state = device_state<TO1, TOs...>;
//};
//
//struct state_path {
//   root_state const* state{nullptr};
//   size_t size{0};
//
//   auto get_last() const noexcept -> std::optional<root_state> {
//      if(size == 0) return std::nullopt;
//      return state[size - 1];
//   }
//
//   auto cleanup() {
//      state = nullptr;
//      size  = 0;
//   }
//};
//
//template<typename = void, typename ... TRANS>
//struct state_transitions {
//   constexpr static auto All_Direct_Transitions =
//      holo::make_tuple(holo::pair_t<typename TRANS::from_state, typename TRANS::to_state>...);
//
//private:
//   template<typename ... STATES>
//   struct to_path {
//      constexpr static auto Num_Of_States = sizeof...(STATES);
//      constexpr static root_state States[] = {
//         STATES::Root_State...
//      };
//      constexpr static state_path Path{States, Num_Of_States};
//   };
//
//public:
//   constexpr static auto get_All_Transitions_Paths() {
//      return holo::product( holo::unique(holo::tuple_t<typename TRANS::from_state ...>),
//                            holo::unique(holo::tuple_t<typename TRANS::to_state ...>))
//      | holo::transform([](auto elem) {
//         return state_transition_algo::find_shortcut(elem, All_Direct_Transitions); });
//   }
//};
//
//struct device_0 {
//   constexpr static uint8_t Device_Id = 0;
//};
//
//struct device_1 {
//   constexpr static uint8_t Device_Id = 1;
//};
//
//struct device_2 {
//   constexpr static uint8_t Device_Id = 2;
//};
//
//struct device_3 {
//   constexpr static uint8_t Device_Id = 3;
//};
//
//using trans = state_transitions<
//   transition_trait<auto (device_state<device_0, __g_PREVIEW(device_1)>) -> __g_PREVIEW(device_2), device_1>,
//   transition_trait<auto (device_state<device_2, __g_PREVIEW(device_1)>) -> __g_PREVIEW(device_1), device_0>,
//   transition_trait<auto (device_state<device_1, __g_PREVIEW(device_0)>) -> __g_PREVIEW(device_1), device_2>>;
//
//namespace {
//   template<typename T> struct S;
//   TEST_CASE("test transition") {
//      //S<decltype(trans::All_Direct_Transitions)> s;
//
//      using from_state = device_state<device_0, __g_PREVIEW(device_1)>;
//      using to_state   = device_state<device_1, __g_PREVIEW(device_0)>;
//      constexpr auto elem = holo::pair_t<from_state, to_state>;
//      constexpr auto shortcut = state_transition_algo::find_shortcut(elem, trans::All_Direct_Transitions);
//
//      constexpr auto trans = trans::get_All_Transitions_Paths();
//      //S<decltype(trans::All_Transitions_Paths)> s;
//   }
//}
//
