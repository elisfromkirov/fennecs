#pragma once

#include <fennecs/core/types.hpp>
#include <fennecs/entity/array.hpp>

#include <vector>

namespace fennecs {

class EntityRegistry {
 public:
  EntityRegistry();

  EntityArray& Array(SizeType index);

  [[nodiscard]] SizeType Size() const;

  SizeType AddArray(const EntityArchetype& archetype, const EntityLayout& layout);

  [[nodiscard]] SizeType FindArray(const EntityArchetype& archetype) const;

 private:
  std::vector<EntityArray> arrays_;
};

}  // namespace fennecs