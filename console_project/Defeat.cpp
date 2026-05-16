#include "Defeat.h"
#include <string>
#include <filesystem>
#include <fstream>
#include "structs.h"
#include "Define.h"
#include "ConsoleDatas.h"
#include "ConsoleControl.h"
#include "LogHelper.h"
#include "File.h"

char* defeat_bg = nullptr;

bool DefeatDataInit()
{
	std::filesystem::path path;
	path = std::filesystem::current_path() / "map_datas" / "defeat_bg.txt";

	if (!FileRead(path, LoadBGData, defeat_bg))
		return false;
	return true;
}

void DefeatUpdate()
{
	if (IsPressKey(VK_ESCAPE))
	{
		current_scene = Scene::TITLE;
	}
}

void DefeatRender()
{
	memcpy(console_back_buffer, defeat_bg, console_size.x * console_size.y);
}

void DefeatDataRelease()
{
	if (defeat_bg != nullptr)
		free(defeat_bg);
}
