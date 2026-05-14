#pragma once

#include "structs.h"

struct Enemy
{
	char id;
	bool enable;
	IntVec2 position;
	IntVec2 direction;
	size_t current_pattern;
};

struct Bullet
{
	char id;
	IntVec2 direction;
};