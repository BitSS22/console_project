#include "ConsoleControl.h"
#include <iostream>
#include <string>
#include "ConsoleDatas.h"

bool IsPressKey(unsigned char key)
{
	return KeyList[key].press;
}

void CursorMove(IntVec2 postion)
{
	SetConsoleCursorPosition(console_handle, postion);
}

inline size_t GetIdx(IntVec2 position)
{
	return GetIdx(position.x, position.y);
}

inline size_t GetIdx(int x, int y)
{
	return y * console_size.x + x;
}
