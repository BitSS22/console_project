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
	// 패턴은 가변길이 2차원배열.
	// 근데 길이가 처음에 고정이니 최종 길이와 각 패턴의 길이를 기록한다면 1차원으로도 가능할듯
	// 패턴 정의
	// 
	// W - wait
	// operand
	// int
	// M - Move
	// operand
	// IntVec2
	// S - Spawn
	// operand
	// position
	// direction
	// id
	// J - jump
	// int
	void* instruct;
	char (*operand)[];
	//char*
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
