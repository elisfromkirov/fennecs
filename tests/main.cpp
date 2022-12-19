#include <fennecs/entity/world.hpp>

#include <iostream>

struct Position {
  float x;
  float y;
  float z;
};

struct Velocity {
  float x;
  float y;
  float z;
};

struct TrackableComponent {
  TrackableComponent()
      : value_{0} {
    std::cout << "default constructor" << std::endl;
  }

  explicit TrackableComponent(int value)
      : value_{value} {
    std::cout << "constructor" << std::endl;
  }

  TrackableComponent(const TrackableComponent& other)
      : value_{other.value_} {
    std::cout << "copy constructor" << std::endl;
  }

  TrackableComponent& operator=(const TrackableComponent& other) {
    std::cout << "copy assignment operator" << std::endl;
    if (this != &other) {
      value_ = other.value_;
    }
    return *this;
  }

  TrackableComponent(TrackableComponent&& other) noexcept
      : value_{other.value_} {
    std::cout << "move constructor" << std::endl;
    other.value_ = 0;
  }

  TrackableComponent& operator=(TrackableComponent&& other) noexcept {
    std::cout << "move assignment operator" << std::endl;
    if (this != &other) {
      value_ = other.value_;
      other.value_ = 0;
    }
    return *this;
  }

  ~TrackableComponent() {
    std::cout << "destructor" << std::endl;
  }

  int value_;
};

struct MoveOnlyComponent {
  MoveOnlyComponent()
      : value_{0} {
  }

  explicit MoveOnlyComponent(int value)
      : value_{value} {
  }

  MoveOnlyComponent(const MoveOnlyComponent& other) = delete;
  MoveOnlyComponent& operator=(const MoveOnlyComponent& other) = delete;

  MoveOnlyComponent(MoveOnlyComponent&& other) noexcept
      : value_{other.value_} {
    other.value_ = 0;
  }

  MoveOnlyComponent& operator=(MoveOnlyComponent&& other) noexcept {
    if (this != &other) {
      value_ = other.value_;
      other.value_ = 0;
    }
    return *this;
  }

 int value_;
};

struct CopyOnlyComponent {
  CopyOnlyComponent()
      : value_{0} {
  }

  explicit CopyOnlyComponent(int value)
      : value_{value} {
  }

  CopyOnlyComponent(const CopyOnlyComponent& other)
      : value_{other.value_} {
  }

  CopyOnlyComponent& operator=(const CopyOnlyComponent& other) {
    if (this != &other) {
      value_ = other.value_;
    }
    return *this;
  }

  CopyOnlyComponent(CopyOnlyComponent&& other) = delete;
  CopyOnlyComponent& operator=(CopyOnlyComponent&& other) = delete;

  int value_;
};

int main() {
  fennecs::EntityWorld world{};
  fennecs::EntityHandle handle = world.AddEntity();
  handle = world.Attach<Position>(handle);
  handle = world.Attach<TrackableComponent>(handle, 5);
  std::cout << handle.Get<TrackableComponent>().value_ << std::endl;
  handle = world.Attach<MoveOnlyComponent>(handle);
  std::cout << handle.Get<TrackableComponent>().value_ << std::endl;
  handle = world.Attach<Velocity>(handle);
  std::cout << handle.Get<TrackableComponent>().value_ << std::endl;
  handle = world.Attach<CopyOnlyComponent>(handle);
  std::cout << handle.Get<TrackableComponent>().value_ << std::endl;
  return 0;
}