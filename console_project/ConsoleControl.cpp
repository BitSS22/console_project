#include "ConsoleControl.h"
#include <iostream>
#include <string>
#include <algorithm>
#include "ConsoleDatas.h"

bool IsPressKey(unsigned char key)
{
	return KeyList[key].press;
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

inline size_t GetIdx(IntVec2 position)
{
	return GetIdx(position.x, position.y);
}

inline size_t GetIdx(int x, int y)
{
	return y * console_size.x + x;
}

inline void InBoundConsoleSize(IntVec2& position)
{
	position.x = std::clamp(position.x, 0, console_size.x - 1);
	position.y = std::clamp(position.y, 0, console_size.y - 1);
}

inline bool IsOutofConsoleSize(IntVec2 position)
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
