#include "ConsoleControl.h"
#include "ConsoleDatas.h"

bool IsPressKey(int key)
{
	return KeyList[key].press;
}

void CursorMove(IntVec2 postion)
{
	SetConsoleCursorPosition(console_handle, postion);
}

void ConsoleClear(char ch = ' ')
{
	DWORD output;
	FillConsoleOutputCharacter(console_handle, ch, console_size.x * console_size.y, IntVec2(), &output);
}

inline size_t GetIdx(IntVec2 position)
{
	return GetIdx(position.x, position.y);
}

inline size_t GetIdx(int x, int y)
{
	return y * console_size.x + x;
}
