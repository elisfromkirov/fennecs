#pragma once

#include <fennecs/entity/array.hpp>
#include <fennecs/entity/handle.hpp>

namespace fennecs {

/**
 * @brief Stream of entities.
 */
class EntityStream {
 public:
  /**
   * @brief Returns next handle to entity or null if all entities have been
   * returned.
   */
  EntityHandle Next();
};

}  // namespace ecs