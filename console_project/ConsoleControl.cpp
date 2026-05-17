#include "ConsoleControl.h"
#include <iostream>
#include <string>
#include <algorithm>
#include "ConsoleDatas.h"
#include <exception>

bool IsKey(unsigned char key, KeyState state)
{
	switch (state)
	{
	case KeyState::DOWN:
		return KeyList[key].down;
	case KeyState::PRESS:
		return KeyList[key].press;
	case KeyState::UP:
		return KeyList[key].up;
	case KeyState::NONE:
		return KeyList[key].none;
	default:
		throw std::exception();
		break;
	}
}

void CursorMove(IntVec2 postion)
{
	SetConsoleCursorPosition(console_handle, postion);
}

void CursorMove(size_t index)
{
	IntVec2 position;
	position.x = static_cast<int>(index) % console_size.x;
	position.y = static_cast<int>(index) / console_size.x;
	CursorMove(position);
}

size_t GetIdx(IntVec2 position)
{
	return GetIdx(position.x, position.y);
}

size_t GetIdx(int x, int y)
{
	return y * console_size.x + x;
}

void InBoundConsoleSize(IntVec2& position)
{
	position.x = std::clamp(position.x, 0, console_size.x - 1);
	position.y = std::clamp(position.y, 0, console_size.y - 1);
}

bool IsOutofConsoleSize(IntVec2 position)
{
	if (position.x < 0)
		return true;
	if (position.x >= console_size.x)
		return true;
	if (position.y < 0)
		return true;
	if (position.y >= console_size.y)
		return true;
	return false;
}
