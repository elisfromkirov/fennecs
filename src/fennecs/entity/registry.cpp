#include <fennecs/entity/registry.hpp>

namespace fennecs {

EntityArray* EntityRegistry::AddArray(const EntityArchetype& archetype,
                                  const EntityLayout& layout) {
  return &arrays_.emplace_back(archetype, layout);
}

EntityArray* EntityRegistry::FindArray(const EntityArchetype& archetype) {
  for (auto& array : arrays_) {
    if (archetype.Equals(array.Archetype())) {
      return &array;
    }
  }
  return nullptr;
}

}  // namespace fennecs