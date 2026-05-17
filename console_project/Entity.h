#pragma once

#include "structs.h"
#include <string>
#include <vector>

enum class ObjectType : char
{
	PLAYER,
	ENEMY,
	OBJECT,
	PLAYER_BULLET,
	ENEMY_BULLET,

	ENUM_SIZE
};

struct Entity
{
	char id;
	bool enable;
	ObjectType object_type;
	IntVec2 position;
	IntVec2 direction;
	std::string_view pattern;
	size_t instruct_iterator;
};

struct EntityData
{
	ObjectType object_type;
	IntVec2 default_direction;
	std::string_view pattern;
};

struct StageData
{
	std::vector<std::pair<char, IntVec2>> entity_datas;
	char* bg;
	IntVec2 player_init_position;
};
