#pragma once

#include <fennecs/entity/array.hpp>
#include <fennecs/entity/handle.hpp>

#include <list>

namespace fennecs {

class EntityWorld;

/**
 * @brief Stream of entities.
 */
class EntityStream {
  friend class EntityWorld;

 public:
  /**
   * @brief Returns next handle to entity or null if all entities have been
   * returned.
   */
  EntityHandle Next();

 private:
  EntityStream(EntityArchetype archetype, std::list<EntityArray>& arrays);

 private:
  EntityArchetype archetype_;
  std::list<EntityArray>& arrays_;
};

}  // namespace ecs