///////////////////////////////////////////////////////////////////////////////
// Velocity.hpp
///////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef VELOCITY_HPP
#define VELOCITY_HPP

#include "Vector.hpp"

struct Velocity {
	constexpr Velocity(float x, float y)
		: v{ x, y }
	{}

	constexpr Velocity() : v{} {}

	Vector v;
};

#endif // !VELOCITY_HPP
