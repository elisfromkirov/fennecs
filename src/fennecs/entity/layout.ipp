#ifndef ENTITY_LAYOUT_IMPL
#error Do not include this file directly
#endif

#include <iostream>

namespace fennecs {

template <typename Component>
SizeType EntityLayout::OffsetOf() const {
//  std::cout << "--------------- internal validation ---------------" << std::endl;
//  std::cout << this << " 0 " << offsets_.count(0) << std::endl;
//  std::cout << this << " 1 " << offsets_.count(1) << std::endl;
//  std::cout << this << " 2 " << offsets_.count(2) << std::endl;
//  std::cout << this << " 3 " << offsets_.count(3) << std::endl;
//  std::cout << this << " 4 " << offsets_.count(4) << std::endl;
//  std::cout << "--------------- internal validation ---------------" << std::endl;

  ASSERT(offsets_.count(ComponentTraits<Component>::Index()) == 1,
         "Attempt ot get offset of component that does not contain in entity");

  return offsets_.at(ComponentTraits<Component>::Index());
}

template <typename Component>
EntityLayout EntityLayout::Attach() const {
//  std::cout << "--------------- internal validation ---------------" << std::endl;
//  std::cout << this << " 0 " << offsets_.count(0) << std::endl;
//  std::cout << this << " 1 " << offsets_.count(1) << std::endl;
//  std::cout << this << " 2 " << offsets_.count(2) << std::endl;
//  std::cout << this << " 3 " << offsets_.count(3) << std::endl;
//  std::cout << this << " 4 " << offsets_.count(4) << std::endl;
//  std::cout << "--------------- internal validation ---------------" << std::endl;
//
//  std::cout << "Attach to layout " << this << " component " << ComponentTraits<Component>::Index() << std::endl;

  ASSERT(offsets_.count(ComponentTraits<Component>::Index()) != 1,
         "Attempt to attach already attached component");

  EntityLayout layout{*this};
  layout.offsets_.emplace(ComponentTraits<Component>::Index(), stride_);
  layout.stride_ += sizeof(Component);

//  std::cout << &layout << " 0 " << layout.offsets_.count(0) << std::endl;
//  std::cout << &layout << " 1 " << layout.offsets_.count(1) << std::endl;
//  std::cout << &layout << " 2 " << layout.offsets_.count(2) << std::endl;
//  std::cout << &layout << " 3 " << layout.offsets_.count(3) << std::endl;
//  std::cout << &layout << " 4 " << layout.offsets_.count(4) << std::endl;
//
//  std::cout << "--------------- internal validation ---------------" << std::endl;
//  std::cout << this << " 0 " << offsets_.count(0) << std::endl;
//  std::cout << this << " 1 " << offsets_.count(1) << std::endl;
//  std::cout << this << " 2 " << offsets_.count(2) << std::endl;
//  std::cout << this << " 3 " << offsets_.count(3) << std::endl;
//  std::cout << this << " 4 " << offsets_.count(4) << std::endl;
//  std::cout << "--------------- internal validation ---------------" << std::endl;

  return layout;
}

template <typename Component>
EntityLayout EntityLayout::Detach() const {
  ASSERT(false, "TODO: Implement it");

  return EntityLayout{};
}

}  // namespace fennecs