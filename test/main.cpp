#include <fennecs/entity/world.hpp>

#include <iostream>

struct TrackableComponent {
  TrackableComponent() {
    std::cout << "default constructor" << std::endl;
  }

  TrackableComponent(const TrackableComponent& other) {
    std::cout << "copy constructor" << std::endl;
  }

  TrackableComponent& operator=(const TrackableComponent& other) {
    std::cout << "copy assignment operator" << std::endl;
    return *this;
  }

  TrackableComponent(TrackableComponent&& other) noexcept {
    std::cout << "move constructor" << std::endl;
  }

  TrackableComponent& operator=(TrackableComponent&& other) noexcept {
    std::cout << "move assignment operator" << std::endl;
    return *this;
  }

  ~TrackableComponent() {
    std::cout << "destructor" << std::endl;
  }
};

struct MoveOnlyComponent {
  MoveOnlyComponent() = default;

  MoveOnlyComponent(const MoveOnlyComponent& other) = delete;
  MoveOnlyComponent& operator=(const MoveOnlyComponent& other) = delete;

  MoveOnlyComponent(MoveOnlyComponent&& other) noexcept = default;
  MoveOnlyComponent& operator=(MoveOnlyComponent&& other) noexcept = default;
};

struct CopyOnlyComponent {
  CopyOnlyComponent() = default;

  CopyOnlyComponent(const CopyOnlyComponent& other) = default;
  CopyOnlyComponent& operator=(const CopyOnlyComponent& other) = default;

  CopyOnlyComponent(CopyOnlyComponent&& other) noexcept = delete;
  CopyOnlyComponent& operator=(CopyOnlyComponent&& other) noexcept = delete;
};

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

struct Acceleration {
  float x;
  float y;
  float z;
};

int main() {
  fennecs::EntityWorld world{};

  {
    fennecs::SizeType amount = 100;
    for (fennecs::SizeType index = 0; index < amount; ++index) {
      fennecs::EntityHandle handle = world.AddEntity();
      handle = world.Attach<Position>(handle);
      handle = world.Attach<Velocity>(handle);
    }
  }

  {
    fennecs::EntityStream stream = world.Query<Position>();
    for (fennecs::EntityHandle handle = stream.Next(); !handle.IsNull(); handle = stream.Next()) {
      handle.Get<Position>().x = 5;
    }
  }

  {
    fennecs::SizeType counter = 0;
    fennecs::EntityStream stream = world.Query<Position, Velocity>();
    for (fennecs::EntityHandle handle = stream.Next(); !handle.IsNull(); handle = stream.Next()) {
      std::cout << "[" << counter++ << "] " << handle.Get<Position>().x << std::endl;
    }
  }

  {
    fennecs::EntityStream stream = world.Query<Position, Velocity>();
    for (fennecs::EntityHandle handle = stream.Next(); !handle.IsNull(); handle = stream.Next()) {
      world.Attach<Acceleration>(handle);
    }
  }

  {
    fennecs::EntityStream stream = world.Query<Acceleration>();
    for (fennecs::EntityHandle handle = stream.Next(); !handle.IsNull(); handle = stream.Next()) {
      handle.Get<Acceleration>().y = 10;
    }
  }

  {
    fennecs::SizeType counter = 0;
    fennecs::EntityStream stream = world.Query<Position, Acceleration>();
    for (fennecs::EntityHandle handle = stream.Next(); !handle.IsNull(); handle = stream.Next()) {
      std::cout << "[" << counter++ << "] " << handle.Get<Position>().x << " "
                << handle.Get<Acceleration>().y << std::endl;
    }
  }

  return 0;
}