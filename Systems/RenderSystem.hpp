///////////////////////////////////////////////////////////////////////////////
// RenderSystem.hpp
///////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef RENDER_SYSTEM_HPP
#define RENDER_SYSTEM_HPP

#include "../Components/Glyph.hpp"
#include "../Components/Position.hpp"
#include "../ECS/Coordinator.hpp"
#include "../ECS/System.hpp"

#include <array>
#include <cmath>
#include <iostream>

class RenderSystem : public System {
public:
    void update() 
	{
		std::cout << "\033[H";
		buf.fill(0xFFFF);

		for (auto const& entity : entities)
		{
			auto& pos = coordinator.get_component<Position>(entity);

			int x = static_cast<int>(std::floor(pos.v.x));
			int y = static_cast<int>(std::floor(pos.v.y));

			if (x < 0)
				x = 0;
			else if (x > 79)
				x = 79;

			if (y < 0)
				y = 0;
			else if (y > 23)
				y = 23;

			buf[y * 80 + x] = entity;
		}

		for (int y = 0; y < 24; y++) {
			for (int x = 0; x < 80; x++) {
				Entity entity = buf[y * 80 + x];
				if (entity == 0xFFFF) {
					std::cout << " ";
					continue;
				}

				auto& glyph = coordinator.get_component<Glyph>(entity);
				switch (glyph.color) {
				case 0:  std::cout << " "; break;
				case 1:  std::cout << "\033[0;31m"; break;
				case 2:  std::cout << "\033[0;32m"; break;
				case 3:  std::cout << "\033[0;33m"; break;
				case 4:  std::cout << "\033[0;34m"; break;
				case 5:  std::cout << "\033[0;35m"; break;
				case 6:  std::cout << "\033[0;36m"; break;
				case 7:  std::cout << "\033[0;37m"; break;
				case 8:  std::cout << "\033[1;30m"; break;
				case 9:  std::cout << "\033[1;31m"; break;
				case 10: std::cout << "\033[1;32m"; break;
				case 11: std::cout << "\033[1;33m"; break;
				case 12: std::cout << "\033[1;34m"; break;
				case 13: std::cout << "\033[1;35m"; break;
				case 14: std::cout << "\033[1;36m"; break;
				case 15: std::cout << "\033[1;37m"; break;
				}

				std::cout << glyph.symbol;
			}
			std::cout << "\n";
		}
    }

private:
	std::array<Entity, 80 * 24> buf{};
};

#endif // !RENDER_SYSTEM_HPP
