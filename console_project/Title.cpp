#include "Title.h"
#include <string>
#include <filesystem>
#include <fstream>
#include "structs.h"
#include "Define.h"
#include "ConsoleDatas.h"
#include "ConsoleControl.h"
#include "LogHelper.h"
#include "File.h"

char* title_bg = nullptr;



bool TitleDataInit()
{
	std::filesystem::path path;
	path = std::filesystem::current_path() / "map_datas" / "title_bg.txt";

	if (!FileRead(path, LoadBGData, title_bg))
		return false;
	return true;
}

void TitleUpdate()
{
	if (IsPressKey(VK_RETURN))
	{
		current_scene = Scene::GAME;
	}
}

void TitleRender()
{
	memcpy(console_back_buffer, title_bg, console_size.x * console_size.y);
}

void TitleDataRelease()
{
	if (title_bg != nullptr)
		free(title_bg);
}
