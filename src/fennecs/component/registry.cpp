#include <fennecs/component/registry.hpp>

#include <iostream>

namespace fennecs {

ComponentVirtualTable& ComponentRegistry::VirtualTable(SizeType index) {
  // std::cout << "Get component with " << index << std::endl;

  ASSERT(virtual_tables_.count(index) == 1,
         "Attempt to get virtual table of component that have not been added");

  return virtual_tables_.at(index);
}

}  // namespace fennecs