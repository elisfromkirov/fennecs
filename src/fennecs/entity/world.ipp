#ifndef WORLD_IMPL
#error Do not include this file directly
#endif

#include <iostream>

namespace fennecs {

template <typename Component, typename... ArgTypes>
EntityHandle EntityWorld::Attach(EntityHandle handle, ArgTypes&& ... args) {
  // std::cout << ComponentTraits<Component>::Index() << std::endl;

  // Check whether component contains in entity.
  // std::cout << __func__ << " " << __LINE__ << std::endl;
  if (handle.template Has<Component>()) {
    return handle;
  }

  // Extract entity from the array where it is.
  // std::cout << __func__ << " " << __LINE__ << std::endl;
  handle.entity_->Unlink();

  // Find appropriate new array.
  // std::cout << __func__ << " " << __LINE__ << std::endl;
  EntityArray& array = FindArrayOnAttach<Component>(handle);

  // Allocate memory for new entity.
  // std::cout << __func__ << " " << __LINE__ << std::endl;
  Entity* entity = entity_allocator_.Allocate(array.Layout());

  // Move component from entity to new entity
  // std::cout << __func__ << " " << __LINE__ << std::endl;
  Move(*handle.archetype_,
       *handle.layout_,
       handle.entity_,
       array.Archetype(),
       array.Layout(),
       entity);

  // Instantiate additional component
  // std::cout << __func__ << " " << __LINE__ << std::endl;
  Uint8* place = entity->Data() + array.Layout().template OffsetOf<Component>();
  new(place) Component(::std::forward<ArgTypes>(args)...);

  // Insert entity to new array.
  // std::cout << __func__ << " " << __LINE__ << std::endl;
  array.Insert(entity);

  // Deallocate memory of entity.
  // std::cout << __func__ << " " << __LINE__ << std::endl;
  entity_allocator_.Deallocate(handle.entity_);

  // Return handle for new entity
  // std::cout << __func__ << " " << __LINE__ << std::endl;
  return EntityHandle{&array.Archetype(), &array.Layout(), entity};
}

template <typename Component>
EntityHandle EntityWorld::Detach(EntityHandle handle) {
}

template <typename Component>
EntityArray& EntityWorld::FindArrayOnAttach(EntityHandle handle) {
  SizeType index = entity_registry_.FindArray(handle.archetype_->template Attach<Component>());
  if (index == entity_registry_.Size()) {
    index = entity_registry_.AddArray(handle.archetype_->template Attach<Component>(),
                                      handle.layout_->template Attach<Component>());

    if (!component_registry_.template HasVirtualTableOf<Component>()) {
      component_registry_.template AddVirtualTableOf<Component>();
    }
  }
  return entity_registry_.Array(index);
}

template <typename Component>
EntityArray& EntityWorld::FindArrayOnDetach(EntityHandle handle) {
}

}  // namespace fennecs

