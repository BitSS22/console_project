#include "ConsoleControl.h"
#include <iostream>
#include <string>
#include "ConsoleDatas.h"

bool IsPressKey(int key)
{
	return KeyList[key].press;
}

void CursorMove(IntVec2 postion)
{
	SetConsoleCursorPosition(console_handle, postion);
}

void ConsoleClear(char ch)
{
	std::string fill(console_size.x, ch);
	for (size_t y = 0; y < console_size.y; ++y)
	{
		CursorMove(IntVec2(0, y));
		std::cout << fill;
	}
}

inline size_t GetIdx(IntVec2 position)
{
	return GetIdx(position.x, position.y);
}

inline size_t GetIdx(int x, int y)
{
	return y * console_size.x + x;
}
