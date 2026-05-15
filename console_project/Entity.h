#pragma once

#include "structs.h"
#include <functional>

enum class ObjectType : char
{
	PLAYER,
	ENEMY,
	OBJECT,
	PLAYER_BULLET,
	ENEMY_BULLET,

	ENUM_SIZE
};

struct Pattern
{
	char* code;
	char* instruct_index;
	size_t instruct_count;
};

struct Entity
{
	char id;
	bool enable;
	ObjectType object_type;
	IntVec2 position;
	IntVec2 direction;
	Pattern* pattern;
	size_t current_pattern_index;
};

struct EntityData
{
	IntVec2 init_direction;
	Pattern* pattern;
};