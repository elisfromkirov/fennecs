#include <fennecs/entity/world.hpp>

#include <iostream>

namespace fennecs {

EntityWorld::EntityWorld() {
  entity_registry_.AddArray(EntityArchetype{}, EntityLayout{});
}

EntityHandle EntityWorld::NewEntity() {
  EntityArray& array = entity_registry_.Array(entity_registry_.FindArray(EntityArchetype{}));
  Entity* entity = entity_allocator_.Allocate(array.Layout());
  array.Insert(entity);
  return EntityHandle{&array.Archetype(), &array.Layout(), entity};
}

void EntityWorld::Move(const EntityArchetype& archetype,
                       const EntityLayout& layout,
                       Entity* entity,
                       const EntityArchetype& new_archetype,
                       const EntityLayout& new_layout,
                       Entity* new_entity) {
  for (SizeType index = 0; index < ComponentMaxIndex(); ++index) {
    if (archetype.Has(index) && new_archetype.Has(index)) {
      ComponentVirtualTable& virtual_table = component_registry_.VirtualTable(index);
      virtual_table.Move(entity->Data() + layout.Offset(index),
                         new_entity->Data() + new_layout.Offset(index));
    }
  }
}

}  // namespace fennecs