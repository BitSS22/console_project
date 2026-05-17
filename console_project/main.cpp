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
		KeyList[i].down = false;
		KeyList[i].press = false;
		KeyList[i].up = false;
		KeyList[i].none = true;
	}

	// data load
	std::filesystem::path path;

	path = std::filesystem::current_path() / "init_datas" / "init_data.txt";
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

	if (!VictoryDataInit())
	{
		Log("Victory Data Init Fail.\n");
		return false;
	}

	if (!DefeatDataInit())
	{
		Log("Defeat Data Init Fail.\n");
		return false;
	}

	// hide cursor
	CONSOLE_CURSOR_INFO consoleCursorInfo;
	consoleCursorInfo.bVisible = FALSE;
	consoleCursorInfo.dwSize = 1;
	SetConsoleCursorInfo(console_handle, &consoleCursorInfo);

	COORD coord = console_size;
	coord.X += 1;
	BOOL b1 = SetConsoleScreenBufferSize(console_handle, coord);

	SMALL_RECT rect;
	rect.Left = 0;
	rect.Top = 0;
	rect.Right = console_size.x - 1;
	rect.Bottom = console_size.y - 1;
	BOOL b2 = SetConsoleWindowInfo(console_handle, TRUE, &rect);

	if (b1 == FALSE || b2 == FALSE)
	{
		Log("콘솔 버퍼 사이즈 조절 실패했는데 이것까지 고치긴 귀찮으니까 사이즈를 적절하게 잘 바꿔서 하셈.\n");
		Log("솔직히 console 화면이 호스팅 되는거라 내가 바꾸던 안바꾸던 전혀 차이가 없는 느낌이긴 한데\n");
		Log("일단 정석은 바꾸는게 맞는 것 같으니까 코드는 실행되도록 냅둠..\n");
	}

	current_scene = Scene::TITLE;

#ifdef LOG
#ifdef CONSOLE_LOG
	Log("Init Succese. Press Any Key.\n");
	auto _ = _getch();
#endif 
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
	VictoryDataRelease();
	DefeatDataRelease();

	timeEndPeriod(1);
}

bool LoadInitData(std::ifstream& file)
{
	std::string line;

	while (std::getline(file, line))
	{
		size_t i = line.find("//");
		if (i != std::string::npos)
			line.resize(i);

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
			if (i < 3 || i >= 300)
			{
				Log("console_size_width need greater then 2 and less then 301.\n");
				return false;
			}

			console_size.x = i;
		}
		else if (key == "console_size_height")
		{
			int i = std::stoi(value);
			if (i < 3 || i >= 300)
			{
				Log("console_size_height need greater then 2 and less then 301.\n");
				return false;
			}

			console_size.y = i;
		}
		else
		{
			Log("Invalid Key name.\n");
			return false;
		}
	}

	console_back_buffer = static_cast<char*>(malloc(console_size.x * console_size.y));
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
		size_t i = line.find("//");
		if (i != std::string::npos)
			line.resize(i);

		if (line.empty())
			continue;

		Log("read data : ", line, '\n');
		size_t index = line.find('=');

		if (index == std::string::npos)
		{
			Log("Not found '=' format.\n");
			return false;
		}

		std::string key(line.data(), index);
		std::string value(line.data() + index + 1, line.size() - index - 1);
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

		// 해석
		std::string code = {};
		bool infinity = true;
		code.reserve(value.size());

		for (size_t i = 0; i < value.size(); )
		{
			const char& ch = value[i];
			
			if (ch == 'W' || ch == 'F' || ch == 'B' || ch == 'L' || ch == 'R')
			{
				size_t start = i + 1;
				size_t end = i + 1;

				while (end < value.size() && value[end] >= '0' && value[end] <= '9')
					++end;
				
				char integer = 0;
				std::from_chars_result&& result = std::from_chars(value.data() + start, value.data() + end, integer);
				if (result.ec == std::errc::invalid_argument || integer == 0 || (ch == 'W' && integer < 0))
				{
					Log("Value is invalid or zero. index", i, ":", ch, "\n");
					return false;
				}
				else if (integer > 100 || integer < -100)
				{
					Log("Value is just great -100 and less 100. index", i, ":", ch, "\n");
					return false;
				}
				else
				{
					if (ch == 'W')
					{
						for (char j = 0; j < integer; ++j)
							code += 'W';
					}
					else
					{
						code += ch;
						code += integer;
					}
				}

				infinity = false;
				i += end - start + 1;
			}
			else if (ch == 'T' || ch == 'K')
			{
				if (i + 1 >= value.size())
				{
					Log("Value is invalid or empty. index", i, ":", ch, "\n");
					return false;
				}
				else
				{
					const char& operand = value[i + 1];
					if (operand != 'F' && operand != 'B' && operand != 'L' && operand != 'R')
					{
						Log("Value is invalid or empty. index", i, ":", ch, "\n");
						return false;
					}
				}

				code += std::string_view(value.data() + i, 2);

				i += 2;
			}
			else if (ch == 'S')
			{
				if (i + 1 >= value.size())
				{
					Log("Value is invalid or empty. index", i, ":", ch, "\n");
					return false;
				}

				code += std::string_view(value.data() + i, 2);

				i += 2;
			}
			else if (ch == 'D')
			{
				code += 'D';
				++i;
				if (i != value.size())
				{
					Log("D can only exist at the end of the pattern. index", i, ":", ch, "\n");
					return false;
				}

				infinity = false;
			}
			else if (ch == ',')
			{
				code += 'W';
				++i;
			}
			else
			{
				Log("Pattern Generate fail. Not found instruct. index", i, ":", ch, "\n");
				return false;
			}
		}

		if (infinity)
		{
			Log("Pattern Generate fail. Is infinity loop.\n");
			return false;
		}

		Log("Make pattern. name:", key, "=", code, "\n");
		pattern_datas.insert(std::make_pair(key, std::move(code)));
	}

	return true;
}

bool LoadEntityData(std::ifstream& file)
{
	std::string line;
	bool is_make = false;

	char id = {};
	EntityData entity_data = {};

	while (std::getline(file, line))
	{
		size_t i = line.find("//");
		if (i != std::string::npos)
			line.resize(i);

		if (line.empty())
			continue;

		Log("read data : ", line, '\n');
		if (line == "define")
		{
			if (is_make)
			{
				Log("define is twice.\n");
				return false;
			}

			Log("define entity start..\n");
			id = 0;
			entity_data.object_type = ObjectType::ENUM_SIZE;
			entity_data.default_direction = IntVec2::ZERO();
			entity_data.pattern = {};
			is_make = true;
			continue;
		}
		if (line == "end")
		{
			if (!is_make)
			{
				Log("end is twice or not declare define.\n");
				return false;
			}

			Log("define entity end. make entity name of ", id, ".\n");
			if (id == 0
			|| entity_data.object_type == ObjectType::ENUM_SIZE
			|| entity_data.default_direction == IntVec2::ZERO()
			|| entity_data.pattern.empty())
			{
				Log("Missing data exists.\n");
				Log("id:", id,"\n");
				Log("object_type:", static_cast<int>(entity_data.object_type),"\n");
				Log("default_direction:", entity_data.default_direction.x, ".", entity_data.default_direction.y, "\n");
				Log("pattern:", entity_data.pattern,"\n");
				return false;
			}

			entity_datas.insert(std::make_pair(id, entity_data));
			is_make = false;
			continue;
		}

		if (!is_make)
		{
			Log("Don't know which one is define.\n");
			return false;
		}

		size_t index = line.find('=');

		if (index == std::string::npos)
		{
			Log("Not found '=' format.\n");
			return false;
		}

		std::string key(line.data(), index);
		std::string value(line.data() + index + 1, line.size() - index - 1);
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

		if (key == "id")
		{
			if (value.size() != 1)
			{
				Log("Id must be one character.\n");
				return false;
			}
			id = value[0];
		}
		else if (key == "object_type")
		{
			if (value == "enemy")
				entity_data.object_type = ObjectType::ENEMY;
			else if (value == "object")
				entity_data.object_type = ObjectType::OBJECT;
			else if (value == "enemy_bullet")
				entity_data.object_type = ObjectType::ENEMY_BULLET;
			else
			{
				Log("The type must be defined as one of the following.\n");
				Log("enemy\n");
				Log("object\n");
				Log("enemy_bullet\n");
				return false;
			}
		}
		else if (key == "pattern_name")
		{
			auto iter = pattern_datas.find(value.data());
			if (iter == pattern_datas.end())
			{
				Log("Not found pattern data. search name:", value, "\n");
				return false;
			}

			entity_data.pattern = iter->second;
		}
		else if (key == "default_direction")
		{
			if (value.size() != 1)
			{
				Log("default_direction must be one character.\n");
				return false;
			}
			else if (value[0] == 'U')
				entity_data.default_direction = IntVec2::UP();
			else if (value[0] == 'R')
				entity_data.default_direction = IntVec2::RIGHT();
			else if (value[0] == 'D')
				entity_data.default_direction = IntVec2::DOWN();
			else if (value[0] == 'L')
				entity_data.default_direction = IntVec2::LEFT();
			else
			{
				Log("The type must be defined as one of the following.\n");
				Log("(U)p (R)ight (D)own (L)eft\n");
				return false;
			}
		}
		else
		{
			Log("Invalid Key name.\n");
			return false;
		}
	}

	return true;
}

void KeyCheck()
{
	for (size_t i = 0; i < KeyList.size(); ++i)
	{
		Key& key = KeyList[i];

		if (GetAsyncKeyState(key.type) & 0x8001) // 이번 프레임 키가 눌림
		{
			if (key.down == true) // 이전 프레임 키가 눌림
			{
				key.down = false;
				key.press = true;
				key.up = false;
				key.none = false;
			}
			else if (key.none == true)  // 이전 프레임 키가 안 눌림
			{
				key.down = true;
				key.press = true;
				key.up = false;
				key.none = false;
			}
		}
		else  // 이번 프레임 키가 안 눌림
		{
			if (key.press == true) // 이전 프레임 키가 눌림
			{
				key.down = false;
				key.press = false;
				key.up = true;
				key.none = true;
			}
			else if (key.up == true)  // 이전 프레임 키가 안 눌림
			{
				key.down = false;
				key.press = false;
				key.up = false;
				key.none = true;
			}
		}
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
	case Scene::VICTORY:
		VictoryUpdate();
		VictoryRender();
		break;
	case Scene::DEFEAT:
		DefeatUpdate();
		DefeatRender();
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
