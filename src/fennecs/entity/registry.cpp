#include <fennecs/entity/registry.hpp>

namespace fennecs {

EntityRegistry::EntityRegistry() {
  arrays_.reserve(8);
}

EntityArray& EntityRegistry::Array(SizeType index) {
  ASSERT(index < Size(), "Index is out of bound");

  return arrays_[index];
}

SizeType EntityRegistry::Size() const {
  return arrays_.size();
}

SizeType EntityRegistry::AddArray(const EntityArchetype& archetype,
                                  const EntityLayout& layout) {
  arrays_.emplace_back(archetype, layout);
  return arrays_.size() - 1;
}

SizeType EntityRegistry::FindArray(const EntityArchetype& archetype) const {
  SizeType index = arrays_.size();
  for (SizeType i = 0; i < arrays_.size(); ++i) {
    if (archetype.Equals(arrays_[i].Archetype())) {
      return i;
    }
  }
  return arrays_.size();
}

}  // namespace fennecs