#pragma once
#include "structs.h"

bool IsPressKey(unsigned char key);

void CursorMove(IntVec2 postion);
inline size_t GetIdx(IntVec2 position);
inline size_t GetIdx(int x, int y);