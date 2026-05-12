#include "ConsoleDatas.h"

bool running_process = true;
HANDLE console_handle = NULL;
IntVec2 console_size = { 0, 0 };
char* console_back_buffer = nullptr;
std::array<Key, (std::numeric_limits<unsigned char>::max)()> KeyList = {};
Scene current_scene = Scene::ENUM_SIZE;