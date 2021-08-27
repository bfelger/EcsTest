///////////////////////////////////////////////////////////////////////////////
// EcsTest.cpp
///////////////////////////////////////////////////////////////////////////////

#include "Components/Glyph.hpp"
#include "Components/Position.hpp"
#include "Components/Velocity.hpp"
#include "ECS/Coordinator.hpp"
#include "ECS/System.hpp"
#include "Systems/PhysicsSystem.hpp"
#include "Systems/RenderSystem.hpp"

#include <chrono>
#include <cstdint>
#include <iostream>
#include <random>
#include <vector>

Coordinator coordinator{};

int main()
{
	coordinator.init();

	// Set aside a bit in Signature for each of these Components.
	coordinator.register_component<Position>();
	coordinator.register_component<Velocity>();
	coordinator.register_component<Glyph>();

	// Call update() with these returned instances.
	auto physics_system = coordinator.register_system<PhysicsSystem>();
	auto render_system = coordinator.register_system<RenderSystem>();

	// Create the Signature for PhysicsSystem and register it.
	// It only cares about Position and Velocity.
	Signature phys_sig;
	phys_sig.set(coordinator.get_component_type<Position>());
	phys_sig.set(coordinator.get_component_type<Velocity>());
	coordinator.set_system_signature<PhysicsSystem>(phys_sig);

	// Create the Signature for RenderSystem and register it.
	// It only cares about Position and Glyph.
	Signature rend_sig;
	rend_sig.set(coordinator.get_component_type<Position>());
	rend_sig.set(coordinator.get_component_type<Glyph>());
	coordinator.set_system_signature<RenderSystem>(rend_sig);

	std::vector<Entity> entities(50);

	// Seed our PRNG's (not serious; for demo purposes only).
	std::default_random_engine generator;
	std::uniform_real_distribution<float> r_pos_x(0.0f, 80.0f);
	std::uniform_real_distribution<float> r_pos_y(0.0f, 24.0f);
	std::uniform_real_distribution<float> r_velocity(-10.0f, 10.0f);
	std::uniform_int_distribution<short> r_glyph('!', '~');
	std::uniform_int_distribution<short> r_color(1, 15);

	for (auto& entity : entities)
	{
		// Create each Entity and assign Components to them.
		entity = coordinator.create_entity();

		// Every time you add a component, SystemManager notifies all Systems
		// that the Entity's Signature has changed, and each one adds or 
		// removes the Entity from its internal list depending on how the 
		// Signature changed.
		coordinator.add_component(entity, Position{ r_pos_x(generator), r_pos_y(generator) });
		coordinator.add_component(entity, Velocity{ r_velocity(generator), r_velocity(generator) });
		coordinator.add_component(entity, Glyph{ static_cast<char>(r_glyph(generator)), static_cast<std::uint8_t>(r_color(generator)) });
	}

	float dt = 0.0f;
	bool quit = false;

	while (!quit)
	{
		auto startTime = std::chrono::high_resolution_clock::now();

		// These can be parallelized. 
		// We should only lock on accessing Position (if we even need to, at 
		// all).
		physics_system->update(dt);
		render_system->update();

		auto stopTime = std::chrono::high_resolution_clock::now();

		dt = std::chrono::duration<float, std::chrono::seconds::period>(stopTime - startTime).count();

		if (std::cin.rdbuf()->in_avail())
			quit = true;
	}

	return 0;
}
