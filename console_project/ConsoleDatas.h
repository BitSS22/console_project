#pragma once

#include <Windows.h>
#include <array>
#include <limits>
#include <unordered_map>
#include <queue>
#include "structs.h"
#include "Define.h"
#include "Entity.h"

inline bool running_process = true;
inline HANDLE console_handle = NULL;

inline char* console_back_buffer = nullptr;
inline IntVec2 console_size = { 0, 0 };
inline std::unordered_map<std::string, const std::string> pattern_datas = {};
inline std::unordered_map<char, const EntityData> entity_datas = {};

inline std::array<Key, (std::numeric_limits<unsigned char>::max)() + 1> KeyList = {};
inline Scene current_scene = Scene::ENUM_SIZE;

inline std::array<Entity, MAX_ENTITY_COUNT> entities = {};

inline constexpr int count_of_second = COUNT_OF_SECOND;
inline constexpr int target_delta_time = count_of_second / TARGET_FRAME;
static_assert(count_of_second% TARGET_FRAME == 0);

static_assert(MAX_ENTITY_COUNT > 0);
static_assert(MAX_PLAYER_BULLET_COUNT > 0);