#include "ConsoleControl.h"
#include "ConsoleDatas.h"

namespace ctrl
{
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
}