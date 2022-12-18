#include <fennecs/entity/handle.hpp>

namespace fennecs {

EntityHandle EntityHandle::Null() {
  return EntityHandle{nullptr, nullptr, nullptr};
}

EntityHandle::EntityHandle(const EntityArchetype* archetype,
                           const EntityLayout* layout,
                           Entity* entity)
    : archetype_{archetype}, layout_{layout}, entity_{entity} {
}

}  // namespace fennecs