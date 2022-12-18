#include <fennecs/entity/archetype.hpp>

namespace fennecs {

bool EntityArchetype::Is(const EntityArchetype& archetype) const {
  return (mask_ & archetype.mask_) == archetype.mask_;
}

bool EntityArchetype::Equals(const EntityArchetype& archetype) const {
  return mask_ == archetype.mask_;
}

bool EntityArchetype::Has(SizeType index) const {
  BitMask mask = ComponentMaskByIndex(index);
  // std::cout << __func__ << " " << __LINE__ << std::endl;
  // std::cout << "\t" << mask_ << std::endl;
  // std::cout << "\t" << mask << std::endl;
  return (mask_ & mask) == mask;
}

EntityArchetype::EntityArchetype(BitMask mask)
    : mask_{mask} {
}

}  // namespace fennecs