#pragma once

#include <fennecs/component/traits.hpp>
#include <fennecs/containers/bit_mask.hpp>
#include <fennecs/core/assert.hpp>
#include <fennecs/core/types.hpp>

namespace fennecs {

/**
 * @brief Archetype contains information about components of which
 * entity consists.
 */
class EntityArchetype {
 public:
  /**
   * @brief Constructs archetype that contains given bit mask.
   */
  EntityArchetype() = default;

  /**
   * @brief Constructs archetype that contains given set of components.
   */
  template <typename... Components>
  EntityArchetype();

  /**
   * @brief Checks whether this archetype is-a given archetype.
   */
  [[nodiscard]] bool Is(const EntityArchetype& archetype) const;

  /**
   * @brief Checks whether this archetype equals to given archetype.
   */
  [[nodiscard]] bool Equals(const EntityArchetype& archetype) const;

  /**
   * @brief Checks whether this archetype has-a component specified by given
   * index.
   */
  [[nodiscard]] bool Has(SizeType index) const;

  /**
   * @brief Checks whether this archetype has-a given component.
   */
  template <typename Component>
  [[nodiscard]] bool Has() const;

  /**
   * @breif Creates archetype copy but with additional component.
   */
  template <typename Component>
  EntityArchetype Attach() const;

  /**
   * @brief Creates archetype copy but without component.
   */
  template <typename Component>
  EntityArchetype Detach() const;

 private:
  EntityArchetype(BitMask mask);

 private:
  BitMask mask_;
};

}  // namespace ecs

#define ARCHETYPE_IMPL
#include <fennecs/entity/archetype.ipp>
#undef ARCHETYPE_IMPL