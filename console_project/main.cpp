#include <cstdio>
#include <iostream>
#include <Windows.h>
#include <filesystem>
#include <fstream>
#include <array>
#include <cstdint>
#include <string>
#include <conio.h>
#pragma comment(lib, "winmm.lib")

// define options
#include "Define.h"

#include "structs.h"
#include "ConsoleControl.h"
#include "File.h"
#include "LogHelper.h"

#include "Scenes.h"
#include "ConsoleDatas.h"
#include "Time.h"

bool Init();
void Release();
void KeyCheck();
void SceneLoop();

int main()
{
	if (!Init())
	{
		Log("Init fail.\n");
		return 0;
	}

	// game loop
	while (running_process)
	{
		KeyCheck();
		SceneLoop();

		AsyncFrame();
	}

	Release();

	return 0;
}

// 가장 먼저 호출되야 함
bool Init()
{
	timeBeginPeriod(1);

	console_handle = GetStdHandle(STD_OUTPUT_HANDLE);

	//std::cout.tie(nullptr);
	//std::ios_base::sync_with_stdio(false);

	// key input
	for (size_t i = 0; i < KeyList.size(); ++i)
	{
		KeyList[i].type = static_cast<unsigned char>(i);
		KeyList[i].press = false;
	}

	// data load
	std::filesystem::path path;

	path = std::filesystem::current_path() / "init_data.txt";
	bool LoadInitData(std::ifstream & file);
	if (!FileRead(path, LoadInitData))
		return false;

	path = std::filesystem::current_path() / "entity_datas" / "pattern.txt";
	bool LoadPatternData(std::ifstream & file);
	if (!FileRead(path, LoadPatternData))
		return false;

	path = std::filesystem::current_path() / "entity_datas" / "entity.txt";
	bool LoadEntityData(std::ifstream & file);
	if (!FileRead(path, LoadEntityData))
		return false;

	if (!TitleDataInit())
	{
		Log("Title Data Init Fail.\n");
		return false;
	}

	if (!GameDataInit())
	{
		Log("Game Data Init Fail.\n");
		return false;
	}

	if (!EndingDataInit())
	{
		Log("Ending Data Init Fail.\n");
		return false;
	}

	// hide cursor
	CONSOLE_CURSOR_INFO consoleCursorInfo;
	consoleCursorInfo.bVisible = FALSE;
	consoleCursorInfo.dwSize = 1;
	SetConsoleCursorInfo(console_handle, &consoleCursorInfo);

	current_scene = Scene::TITLE;

#ifdef CONSOLE_LOG
	Log("Init Succese. Press Any Key.\n");
	auto _ = _getch();
#endif 

	TimeInit();

	return true;
}

void Release()
{
	if (console_back_buffer != nullptr)
		free(console_back_buffer);

	TitleDataRelease();
	GameDataRelease();
	EndingDataRelease();

	timeEndPeriod(1);
}

bool LoadInitData(std::ifstream& file)
{
	std::string line;

	while (std::getline(file, line))
	{
		if (line.empty())
			continue;

		Log("read data : ", line, '\n');
		size_t index = line.find('=');

		if (index == std::string::npos)
		{
			Log("Not found '=' format.\n");
			return false;
		}

		std::string key = line.substr(0, index);
		std::string value = line.substr(index + 1);
		if (value.empty())
		{
			Log("Not found Value Data.\n");
			return false;
		}

		if (key == "console_size_width")
		{
			int i = std::stoi(value);
			if (i < 5)
			{
				Log("console_size_width need greater then 4.\n");
				return false;
			}

			console_size.x = i;
		}
		else if (key == "console_size_height")
		{
			int i = std::stoi(value);
			if (i < 5)
			{
				Log("console_size_height need greater then 4.\n");
				return false;
			}

			console_size.y = i;
		}
		else
		{
			Log("Not found Key Data.\n");
			return false;
		}
	}

	console_back_buffer = static_cast<char*>(malloc(sizeof(console_size.x * console_size.y)));
	if (!console_back_buffer)
	{
		Log("Buffer Allocate Fail.\n");
		return false;
	}

	return true;
}

bool LoadPatternData(std::ifstream& file)
{
	std::string line;

	while (std::getline(file, line))
	{
		if (line.empty())
			continue;

		Log("read data : ", line, '\n');
		size_t index = line.find('=');

		if (index == std::string::npos)
		{
			Log("Not found '=' format.\n");
			return false;
		}

		std::string key = line.substr(0, index);
		std::string value = line.substr(index + 1);
		if (value.empty())
		{
			Log("Not found Value Data.\n");
			return false;
		}
		if (key.empty())
		{
			Log("Not found Key Data.\n");
			return false;
		}

		if (pattern_datas.contains(key))
		{
			Log("Contains pattern data.\n");
			return false;
		}
		pattern_datas.insert(std::make_pair(key, value));
	}

	return true;
}

bool LoadEntityData(std::ifstream& file)
{
	//TODO. 만드셈
	std::string line;

	while (std::getline(file, line))
	{
		if (line.empty())
			continue;

		Log("read data : ", line, '\n');
		size_t index = line.find('=');

		if (index == std::string::npos)
		{
			Log("Not found '=' format.\n");
			return false;
		}

		std::string key = line.substr(0, index);
		std::string value = line.substr(index + 1);
		if (value.empty())
		{
			Log("Not found Value Data.\n");
			return false;
		}
		if (key.empty())
		{
			Log("Not found Key Data.\n");
			return false;
		}

		if (pattern_datas.contains(key))
		{
			Log("Contains pattern data.\n");
			return false;
		}
		pattern_datas.insert(std::make_pair(key, value));
	}

	return true;
}

void KeyCheck()
{
	for (size_t i = 0; i < KeyList.size(); ++i)
	{
		KeyList[i].press = GetAsyncKeyState(static_cast<int>(KeyList[i].type)) & 0x8001;
	}
}

void SceneLoop()
{
	// back buffer clear
	memset(console_back_buffer, ' ', console_size.x * console_size.y);

	switch (current_scene)
	{
	case Scene::TITLE:
		TitleUpdate();
		TitleRender();
		break;
	case Scene::GAME:
		GameUpdate();
		GameRender();
		break;
	case Scene::ENDING:
		EndingUpdate();
		EndingRender();
		break;
	default:
		Log("Unknown scene. current_scene : ", static_cast<int>(current_scene), '\n');
		running_process = false;
		break;
	}

	// buffer draw
	for (int y = 0; y < console_size.y; ++y)
	{
		CursorMove(IntVec2(0, y));
		std::string_view view(console_back_buffer + (console_size.x * y), console_size.x);
		std::cout << view;
	}
}
