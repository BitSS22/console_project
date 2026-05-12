#pragma once

#include <Windows.h>
#include <array>
#include <limits>
#include "structs.h"

extern bool running_process;
extern HANDLE console_handle;
extern IntVec2 console_size;
extern char* console_back_buffer;
extern std::array<Key, (std::numeric_limits<unsigned char>::max)()> KeyList;
extern Scene current_scene;