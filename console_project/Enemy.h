#pragma once

#include "structs.h"

struct Enemy
{
	char id;
	bool enable;
	IntVec2 position;
	IntVec2 direction;
	size_t current_pattern_index;
};

struct Bullet
{
	char id;
	bool enable;
	IntVec2 position;
	IntVec2 direction;
	size_t current_pattern_index;
};