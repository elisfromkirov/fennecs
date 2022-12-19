#include <fennecs/component/registry.hpp>

namespace fennecs {

ComponentVirtualTable& ComponentRegistry::VirtualTable(SizeType index) {
  ASSERT(virtual_tables_.count(index) == 1,
         "Attempt to get virtual table of unregistered component");

  return virtual_tables_.at(index);
}

}  // namespace fennecs