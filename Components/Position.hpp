///////////////////////////////////////////////////////////////////////////////
// Position.hpp
///////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef POSITION_HPP
#define POSITION_HPP

#include "Vector.hpp"

struct Position {
	constexpr Position(float x, float y)
		: v{ x, y }
	{}

	constexpr Position() : v{} {}

	Vector v;
};

#endif // !POSITION_HPP
