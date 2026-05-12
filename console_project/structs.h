#pragma once
#include <exception>
#include <Windows.h>

enum class Scene
{
	TITLE,
	GAME,
	ENDING,

	ENUM_SIZE
};

struct Key
{
	char type;
	bool press;
};

struct IntVec2
{
	int x = 0;
	int y = 0;

	friend IntVec2 operator+(IntVec2 left, IntVec2 right)
	{
		return { left.x + right.x, left.y + right.y };
	}
	friend IntVec2 operator-(IntVec2 left, IntVec2 right)
	{
		return { left.x - right.x, left.y - right.y };
	}
	friend IntVec2 operator*(IntVec2 left, int scalar)
	{
		return { left.x * scalar, left.y * scalar };
	}
	friend IntVec2 operator/(IntVec2 left, int scalar)
	{
		// 일단은 0처리는 예외를 던져버림
		if (scalar == 0)
			throw std::exception("division of zero.");
		return { left.x / scalar, left.y / scalar };
	}
	friend bool operator==(IntVec2 left, IntVec2 right)
	{
		return left.x == right.x && left.y == right.y;
	}
	friend bool operator!=(IntVec2 left, IntVec2 right)
	{
		return !(left == right);
	}
	operator COORD() const
	{
		COORD coord;
		coord.X = x;
		coord.Y = y;
		return coord;
	}
};