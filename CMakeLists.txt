# CMakeList.txt : CMake project for EcsTest, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("EcsTest")

set (CMAKE_CXX_STANDARD 20)

# Add source to this project's executable.
add_executable (EcsTest "EcsTest.cpp"  "ECS/Component.hpp" "ECS/ComponentArray.hpp" "ECS/ComponentManager.hpp" "ECS/Coordinator.hpp" "ECS/Entity.hpp" "ECS/EntityManager.hpp" "ECS/System.hpp" "ECS/SystemManager.hpp" "Systems/PhysicsSystem.hpp" "ECS/Signature.hpp" "Systems/RenderSystem.hpp" "Components/Vector.hpp" "Components/Position.hpp" "Components/Velocity.hpp" "Components/Glyph.hpp")

# TODO: Add tests and install targets if needed.
