#pragma once

#include <Windows.h>
#include <array>
#include <limits>
#include "structs.h"
#include "Define.h"

inline bool running_process = true;
inline HANDLE console_handle = NULL;
inline IntVec2 console_size = { 0, 0 };
inline char* console_back_buffer = nullptr;
inline std::array<Key, (std::numeric_limits<unsigned char>::max)()> KeyList = {};
inline Scene current_scene = Scene::ENUM_SIZE;

inline constexpr int count_of_second = COUNT_OF_SECOND;
inline constexpr int target_delta_time = count_of_second / TARGET_FRAME;
static_assert(count_of_second % TARGET_FRAME == 0);