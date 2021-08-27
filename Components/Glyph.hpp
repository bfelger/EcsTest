///////////////////////////////////////////////////////////////////////////////
// Glyph.hpp
///////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef GLYPH_HPP
#define GLYPH_HPP

#include <cstdint>

struct Glyph {
	constexpr Glyph(char symbol, std::uint8_t color)
		: symbol{ symbol }
		, color{ color }
	{}

	constexpr Glyph() : Glyph{ ' ', 1 } {}

	char symbol;
	std::uint8_t color;
};

#endif // !GLYPH_HPP
