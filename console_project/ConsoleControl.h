#pragma once
#include "structs.h"

bool IsPressKey(unsigned char key);

void CursorMove(IntVec2 postion);
void CursorMove(size_t index);
inline size_t GetIdx(IntVec2 position);
inline size_t GetIdx(int x, int y);
inline void InBoundConsoleSize(IntVec2& position);
inline bool IsOutofConsoleSize(IntVec2 position);