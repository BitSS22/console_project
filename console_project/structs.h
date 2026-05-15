#pragma once
#include <exception>
#include <Windows.h>
#include <cmath>

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
		COORD coord = { x, y };
		return coord;
	}
	friend IntVec2 GetDirection(IntVec2 vector)
	{
		if (vector.x == 0 && vector.y == 0)
			throw std::exception("Is Zero Vector.");

		int x = 0;
		int y = 0;

		if (abs(vector.x) >= abs(vector.y))
		{
			x = vector.x;
		}
		if (abs(vector.x) <= abs(vector.y))
		{
			x = vector.y;
		}

		if (vector.x != 0)
		{
			vector.x /= abs(vector.x);
		}
		if (vector.y != 0)
		{
			vector.y /= abs(vector.y);
		}

		return IntVec2(x, y);
	}
};

