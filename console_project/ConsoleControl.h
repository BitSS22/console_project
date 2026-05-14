#pragma once
#include "structs.h"

bool IsPressKey(int key);

void CursorMove(IntVec2 postion);
void ConsoleClear(char ch = ' ');
inline size_t GetIdx(IntVec2 position);
inline size_t GetIdx(int x, int y);