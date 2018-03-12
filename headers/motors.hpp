// Motor Setup
// Roadant 2018

// Imported once
#pragma once

#include "macros.hpp"

/**
FUNCTION DEFINITIONS
**/

// Forward or backward, pin, and rotation speed
void motorMove(int, int, float);

// Moves motors forward at a given float speed for a given time
void travel(float, float);