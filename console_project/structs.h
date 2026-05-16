#pragma once
#include <exception>
#include <Windows.h>
#include <cmath>

#include "LogHelper.h"

enum class Scene
{
	TITLE,
	GAME,
	ENDING,

	ENUM_SIZE
};

//적이 가질 데이터
//현재 위치
//움직임 패턴(정의된 움직임의 조합 : 공격, 움직임, 회전 등, 루프로 작동)
//패턴 iterator
//앞(forward) 방향
//공격 패턴(정의 된 것 중 하나)

struct Key
{
	unsigned char type;
	bool press;
};

enum class IntVec2Rotate
{
	C0,
	C90,
	C180,
	C270
};

enum class Direction
{
	FORWARD,
	RIGHT,
	BACK,
	LEFT
};

struct IntVec2
{
	int x = 0;
	int y = 0;

	friend IntVec2 operator+(IntVec2 left, IntVec2 right)
	{
		return { left.x + right.x, left.y + right.y };
	}
	IntVec2& operator+=(IntVec2 other)
	{
		x += other.x;
		y += other.y;
		return *this;
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
		COORD coord = { static_cast<short>(x), static_cast<short>(y) };
		return coord;
	}
	static int Dot(IntVec2 left, IntVec2 right)
	{
		return left.x * right.x + left.y * right.y;
	}
	static int Cross(IntVec2 left, IntVec2 right)
	{
		return left.x * right.y - left.y * right.x;
	}
	static IntVec2 Rotate(IntVec2 vector, IntVec2Rotate rotate)
	{
		switch (rotate)
		{
		case IntVec2Rotate::C0:
			return vector;
		case IntVec2Rotate::C90:
			return { vector.y, -vector.x };
		case IntVec2Rotate::C180:
			return { -vector.x, -vector.y };
		case IntVec2Rotate::C270:
			return { -vector.y, vector.x };
		default:
			Log("IntVec2 rotate in invalid argument.\n");
			return {};
		}
	}

	constexpr static IntVec2 UP() { return { 0, -1 }; }
	constexpr static IntVec2 LEFT() { return { -1, 0 }; }
	constexpr static IntVec2 RIGHT() { return { 1, 0 }; }
	constexpr static IntVec2 DOWN() { return { 0, 1 }; }
	constexpr static IntVec2 ZERO() { return { 0, 0 }; }
};

