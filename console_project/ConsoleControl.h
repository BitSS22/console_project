#pragma once
#include "structs.h"

namespace ctrl
{
	bool IsPressKey(int key);

	void CursorMove(IntVec2 postion);
	void ConsoleClear(char ch);
}