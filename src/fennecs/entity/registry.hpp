#pragma once

#include <fennecs/core/types.hpp>
#include <fennecs/entity/array.hpp>

#include <list>

namespace fennecs {

class EntityRegistry {
 public:
  EntityArray* AddArray(const EntityArchetype& archetype, const EntityLayout& layout);

  EntityArray* FindArray(const EntityArchetype& archetype);

 private:
  std::list<EntityArray> arrays_;
};

}  // namespace fennecs