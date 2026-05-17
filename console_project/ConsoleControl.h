#pragma once
#include "structs.h"

bool IsPressKey(unsigned char key);

void CursorMove(IntVec2 postion);
void CursorMove(size_t index);
size_t GetIdx(IntVec2 position);
size_t GetIdx(int x, int y);
void InBoundConsoleSize(IntVec2& position);
bool IsOutofConsoleSize(IntVec2 position);