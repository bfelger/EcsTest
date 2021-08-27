///////////////////////////////////////////////////////////////////////////////
// PhysicsSystem.hpp
///////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef PHYSICS_SYSTEM_HPP
#define PHYSICS_SYSTEM_HPP

#include "../Components/Position.hpp"
#include "../Components/Velocity.hpp"
#include "../ECS/Coordinator.hpp"
#include "../ECS/System.hpp"

extern Coordinator coordinator;

class PhysicsSystem : public System {
public:

    void update(float dt)
    {
		for (auto const& entity : entities)
		{
			auto& pos = coordinator.get_component<Position>(entity);
			auto& vel = coordinator.get_component<Velocity>(entity);

			pos.v.x += vel.v.x * dt;
			pos.v.y += vel.v.y * dt;

			if (pos.v.x < 0.0f) {
				pos.v.x = 0.0f - pos.v.x;
				vel.v.x = 0.0f - vel.v.x;
			}
			else if (pos.v.x >= 79.9f) {
				pos.v.x = 79.9f - (pos.v.x - 79.9f);
				vel.v.x = 0.0f - vel.v.x;
			}

			if (pos.v.y < 0.0f) {
				pos.v.y = 0.0f - pos.v.y;
				vel.v.y = 0.0f - vel.v.y;
			}
			else if (pos.v.y >= 23.9f) {
				pos.v.y = 23.9f - (pos.v.y - 23.9f);
				vel.v.y = 0.0f - vel.v.y;
			}
		}
    }

private:
};

#endif // !PHYSICS_SYSTEM_HPP
