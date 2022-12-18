#ifndef ARCHETYPE_IMPL
#error Do not include this file directly
#endif

#include <iostream>

namespace fennecs {

namespace detail {

template <typename... Components>
struct Mask;

template <typename Component>
struct Mask<Component> {
  static const BitMask kValue = ComponentTraits<Component>::Mask();
};

template <typename Component, typename... Components>
struct Mask<Component, Components...> {
  static const BitMask kValue = ComponentTraits<Component>::Mask() | Mask<Components...>::kValue;
};

}  // namespace detail

template <typename... Components>
EntityArchetype::EntityArchetype()
    : mask_{detail::Mask<Components...>::kValue} {
}

template <typename Component>
bool EntityArchetype::Has() const {
  BitMask mask = ComponentTraits<Component>::Mask();
  return (mask_ & mask) == mask;
}

template <typename Component>
EntityArchetype EntityArchetype::Attach() const {
//  std::cout << __func__ << " " << __LINE__ << std::endl;
//  std::cout << "\t" << mask_ << std::endl;
//  std::cout << "\t" << ComponentTraits<Component>::Mask() << std::endl;
//  std::cout << "\t" << (mask_ | ComponentTraits<Component>::Mask()) << std::endl;

  return EntityArchetype{mask_ | ComponentTraits<Component>::Mask()};
}

template <typename Component>
EntityArchetype EntityArchetype::Detach() const {
  return EntityArchetype{mask_ & (~ComponentTraits<Component>::Mask())};
}

}  // namespace fennecs