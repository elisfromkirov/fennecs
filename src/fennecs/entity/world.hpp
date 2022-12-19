#pragma once

#include <fennecs/core/utility.hpp>
#include <fennecs/component/registry.hpp>
#include <fennecs/entity/allocator.hpp>
#include <fennecs/entity/archetype.hpp>
#include <fennecs/entity/array.hpp>
#include <fennecs/entity/handle.hpp>
#include <fennecs/entity/impl.hpp>
#include <fennecs/entity/layout.hpp>
#include <fennecs/entity/registry.hpp>

namespace fennecs {

class EntityWorld {
 public:
  EntityWorld();

  EntityHandle NewEntity();

  template <typename Component, typename... ArgTypes>
  EntityHandle Attach(EntityHandle handle, ArgTypes&& ... args);

  template <typename Component>
  EntityHandle Detach(EntityHandle handle);

 private:
  template <typename Component>
  EntityArray* FindArrayOnAttach(EntityHandle handle);

  template <typename Component>
  EntityArray* FindArrayOnDetach(EntityHandle handle);

  void Move(const EntityArchetype& archetype,
            const EntityLayout& layout,
            Entity* entity,
            const EntityArchetype& new_archetype,
            const EntityLayout& new_layout,
            Entity* new_entity);

 private:
  ComponentRegistry component_registry_;
  EntityAllocator entity_allocator_;
  EntityRegistry entity_registry_;
};

}  // namespace ecs

#define WORLD_IMPL
#include <fennecs/entity/world.ipp>
#undef WORLD_IMPL