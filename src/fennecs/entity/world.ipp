#ifndef WORLD_IMPL
#error Do not include this file directly
#endif

#include <iostream>

namespace fennecs {

template <typename Component, typename... ArgTypes>
EntityHandle EntityWorld::Attach(EntityHandle handle, ArgTypes&& ... args) {
  // Check whether component contains in entity.
  if (handle.template Has<Component>()) {
    return handle;
  }

  // Extract entity from the array where it is.
  handle.entity_->Unlink();

  // Find appropriate new array.
  EntityArray* array = FindArrayOnAttach<Component>(handle);

  // Allocate memory for new entity.
  Entity* entity = entity_allocator_.Allocate(array->Layout());

  // Move component from entity to new entity
  Move(*handle.archetype_,
       *handle.layout_,
       handle.entity_,
       array->Archetype(),
       array->Layout(),
       entity);

  // Instantiate additional component
  Uint8* place = entity->Data() + array->Layout().template OffsetOf<Component>();
  new(place) Component(::std::forward<ArgTypes>(args)...);

  // Insert entity to new array.
  array->Insert(entity);

  // Deallocate memory of entity.
  entity_allocator_.Deallocate(handle.entity_);

  // Return handle for new entity
  return EntityHandle{&array->Archetype(), &array->Layout(), entity};
}

template <typename Component>
EntityHandle EntityWorld::Detach(EntityHandle handle) {
  ASSERT(false, "TODO: Implement it!");

  return EntityHandle::Null();
}

template <typename Component>
EntityArray* EntityWorld::FindArrayOnAttach(EntityHandle handle) {
  EntityArray* array = entity_registry_.FindArray(handle.archetype_->template Attach<Component>());
  if (array != nullptr) {
    return array;
  }

  if (!component_registry_.template HasVirtualTableOf<Component>()) {
    component_registry_.template RegisterVirtualTableOf<Component>();
  }

  return entity_registry_.AddArray(handle.archetype_->template Attach<Component>(),
                                   handle.layout_->template Attach<Component>());
}

template <typename Component>
EntityArray* EntityWorld::FindArrayOnDetach(EntityHandle handle) {
  ASSERT(false, "TODO: Implement it!");

  return nullptr;
}

}  // namespace fennecs