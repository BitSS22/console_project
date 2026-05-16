#include "Victory.h"
#include <string>
#include <filesystem>
#include <fstream>
#include "structs.h"
#include "Define.h"
#include "ConsoleDatas.h"
#include "ConsoleControl.h"
#include "LogHelper.h"
#include "File.h"

char* victory_bg = nullptr;

bool VictoryDataInit()
{
	std::filesystem::path path;
	path = std::filesystem::current_path() / "map_datas" / "victory_bg.txt";

	if (!FileRead(path, LoadBGData, victory_bg))
		return false;
	return true;
}

void VictoryUpdate()
{
	if (IsPressKey(VK_ESCAPE))
	{
		current_scene = Scene::TITLE;
	}
}

void VictoryRender()
{
	memcpy(console_back_buffer, victory_bg, console_size.x * console_size.y);
}

void VictoryDataRelease()
{
	if (victory_bg != nullptr)
		free(victory_bg);
}
