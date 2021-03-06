///////////////////////////////////////////////////////////////////////////////
// Signature.hpp
///////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef SIGNATURE_HPP
#define SIGNATURE_HPP

#include "Component.hpp"

#include <bitset>

// Which components does this Entity have?
using Signature = std::bitset<MAX_COMPONENTS>;

#endif //!SIGNATURE_HPP
