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

char* title_data = nullptr;

bool Work(std::ifstream& file)
{
	title_data = static_cast<char*>(malloc(sizeof(console_size.x * console_size.y)));
	if (!title_data)
	{
		Log("Buffer Allocate Fail.\n");
		return false;
	}

	std::string line;

	size_t lineCount = 0;

	while (std::getline(file, line))
	{
		if (line.length() > console_size.x)
		{
			Log("The width is too large.\nline : ", lineCount + 1, ", length : ", line.length(), '\n');
			return false;
		}

		if (lineCount >= console_size.y)
		{
			Log("The height is too high.\nline : ", lineCount + 1, ", length : ", line.length(), '\n');
			return false;
		}

		if (line.length() < console_size.x)
			line.resize(console_size.x, ' ');

		Log("read data : ", line, '\n');
		memcpy(title_data + (lineCount * console_size.x), line.c_str(), line.size());

		++lineCount;
	}

	if (lineCount < console_size.y)
	{
		memset(title_data + (lineCount * console_size.x), ' ', (console_size.y - lineCount) * console_size.x);
	}

	return true;
}

bool TitleDataInit()
{
	std::filesystem::path path;
	path = std::filesystem::current_path() / "map_datas" / "title.txt";
	if (!FileRead(path, Work))
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
	memcpy(console_back_buffer, title_data, console_size.x * console_size.y);
}

void TitleDataRelease()
{
	if (title_data != nullptr)
		free(title_data);
}
