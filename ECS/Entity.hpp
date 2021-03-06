///////////////////////////////////////////////////////////////////////////////
// Entity.hpp
///////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <cstdint>

// A thing... or maybe just an index to a thing.
using Entity = std::uint32_t;

const Entity MAX_ENTITIES = 10000;

#endif // !ENTITY_HPP
