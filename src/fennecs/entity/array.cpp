#include <fennecs/entity/array.hpp>

namespace fennecs {

EntityArray::EntityArray(const EntityArchetype& archetype, const EntityLayout& layout)
    : archetype_{archetype},
      layout_{layout} {
}

const EntityArchetype& EntityArray::Archetype() const {
  return archetype_;
}

const EntityLayout& EntityArray::Layout() const {
  return layout_;
}

Entity* EntityArray::Head() {
  return entities_.Tail()->AsContent();
}

Entity* EntityArray::Tail() {
  return entities_.Tail()->AsContent();
}

void EntityArray::Insert(Entity* node) {
  entities_.Insert(node);
}

}  // namespace fennecs
