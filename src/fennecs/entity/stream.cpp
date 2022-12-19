#include <fennecs/entity/stream.hpp>

namespace fennecs {

EntityHandle EntityStream::Next() {
  ASSERT(false, "TODO: Implememt it");
  return EntityHandle::Null();
}

EntityStream::EntityStream(EntityArchetype archetype, std::list<EntityArray>& arrays)
    : archetype_{archetype},
      arrays_{arrays} {
}

}  // namespace fennecs