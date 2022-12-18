#include <fennecs/entity/layout.hpp>

namespace fennecs {

EntityLayout EntityLayout::Empty() {
  return EntityLayout{};
}

SizeType EntityLayout::Stride() const {
  return stride_;
}

SizeType EntityLayout::Offset(SizeType index) const {
//  std::cout << "--------------- internal validation ---------------" << std::endl;
//  std::cout << this << " 0 " << offsets_.count(0) << std::endl;
//  std::cout << this << " 1 " << offsets_.count(1) << std::endl;
//  std::cout << this << " 2 " << offsets_.count(2) << std::endl;
//  std::cout << this << " 3 " << offsets_.count(3) << std::endl;
//  std::cout << this << " 4 " << offsets_.count(4) << std::endl;
//  std::cout << "--------------- internal validation ---------------" << std::endl;

//  std::cout << "Offset of component " << index << " in layout " << this << std::endl;

  ASSERT(offsets_.count(index) == 1,
         "Attempt to get offset of component that does not contain in entity");

  return offsets_.at(index);
}

}  // namespace fennecs