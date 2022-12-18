#ifndef REGISTRY_IMPL
#error Do not include this file directly
#endif

#include <iostream>

namespace fennecs {

template <typename Component>
void ComponentRegistry::AddVirtualTableOf() {
  ASSERT(virtual_tables_.count(ComponentTraits<Component>::Index()) == 0,
         "Attempt to register already registered component");
  // std::cout << "Add component with index " << ComponentTraits<Component>::Index() << std::endl;

  virtual_tables_.emplace(ComponentTraits<Component>::Index(),
                          ComponentVirtualTable::Of<Component>());
}

template <typename Component>
bool ComponentRegistry::HasVirtualTableOf() {
  return virtual_tables_.count(ComponentTraits<Component>::Index()) == 1;
}

}  // namespace fennecs