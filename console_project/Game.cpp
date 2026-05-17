#include "Game.h"
#include <string>
#include <filesystem>
#include <fstream>
#include "structs.h"
#include "Define.h"
#include "ConsoleDatas.h"
#include "ConsoleControl.h"
#include "LogHelper.h"
#include "File.h"

enum class State
{
	GAME_INIT,
	STAGE_READY,
	IN_GAME,
	ENTITIES_LIFE_MANAGEMENT
};

struct Player
{
	IntVec2 position;
	IntVec2 direction;
};

static State game_state = State::GAME_INIT;

char* game_defualt_bg = nullptr;
std::vector<StageData> stage_datas = {};
size_t current_stage = 0;
Player player = {};



bool GameDataInit()
{
	std::filesystem::path path;
	path = std::filesystem::current_path() / "map_datas" / "stage" / "game_defualt_bg.txt";
	if (std::filesystem::exists(path))
	{
		if (!FileRead(path, LoadBGData, game_defualt_bg))
			return false;
	}
	else
	{
		Log("File does not exist. ", path, "\n");
	}

	path = std::filesystem::current_path() / "map_datas" / "stage" / "stage_info.txt";
	bool LoadStageInfoData(std::ifstream& file);
	if (!FileRead(path, LoadStageInfoData))
		return false;

	return true;
}

void StateGameInit()
{
	current_stage = 0;
	player.position = IntVec2::ZERO();
	player.direction = IntVec2::DOWN();

	game_state = State::STAGE_READY;
}

void StateStageReady()
{
	// player position set.
	// entites clear.
	// entites create.
	player.position = stage_datas[current_stage].player_init_position;
}

void StateInGame()
{

}

void StateEntitiesLifeManagement()
{

}

void GameUpdate()
{
	// TODO. 더럽게 많은 인 게임 로직
	// stage 전환 scene 전환 entuty 로직 등을 전부 넣으세요~
	
	switch (game_state)
	{
	case State::GAME_INIT:
		StateGameInit();
		break;
	case State::STAGE_READY:
		StateStageReady();
		break;
	case State::IN_GAME:
		StateInGame();
		break;
	case State::ENTITIES_LIFE_MANAGEMENT:
		StateEntitiesLifeManagement();
		break;
	default:
		Log("Critical error. not found game state.\n");
		return;
	}
	// 업데이트에서 할 일

	// 현재 stage 정보는 전역 변수로 가지고 있음
	
	// 현재 스테이지에 대한 초기화
	// player position set.
	// entites clear.
	// entites create.
	// 모든 작업 종료 후 게임 진행으로 넘어간다.
	
	// 게임 진행중
	// 플레이어 조작 입력
	// 방향키 + 공격 + 무기 변경 -> 그냥 하드코딩으로 하자
	// entities 돌면서 패턴 실행
	// 여기서 생성, 파괴는 이벤트 큐에 삽입 후 이번 프레임 종료 후 처리
	// 모든 위치 값과 패턴 처리
	
	// 특정 그룹끼리의 충돌 처리
	// player - enemy = player 사망 -> 스테이지 종료
	// player - enemy_bullet = player 사망 -> 스테이지 종료
	// player_bullet - enemy = enemy 사망
	// object에 대해서는 아직 구현할 처리 없음




	// 스테이지 종료(클리어) 작업
	// 다음 스테이지가 존재하는지 검사.
	// 존재한다면 현재 stage index 변경 후 스테이지 초기화 단계로.
	// 없다면 게임 클리어.
	// game 상태를 종료하고 victory 상태로 변경.
	// 
	// 스테이지 종료(사망) 작업
	// game 상태를 종료하고 defeat 상태로 변경.
	

	// entites 돌면서 











	if (IsPressKey('0'))
	{
		current_scene = Scene::TITLE;
	}
}

void GameRender()
{
	// back ground render
	char* bg = stage_datas[current_stage].bg;

	if (bg == nullptr)
		bg = game_defualt_bg;

	if (bg != nullptr)
		memcpy(console_back_buffer, bg, console_size.x * console_size.y);

	// TODO. 게임 렌더 내용을 넣으세요~

	// 렌더에서 할 일
	// entities 돌면서 맞는 위치에 대해 id 값 쓰기
}

void GameDataRelease()
{
	if (game_defualt_bg != nullptr)
		free(game_defualt_bg);

	for (size_t i = 0; i < stage_datas.size(); ++i)
	{ 
		if (stage_datas[i].bg != nullptr)
		{
			free(stage_datas[i].bg);
		}
	}
}

bool LoadStageInfoData(std::ifstream& file)
{
	std::string line;
	
	while (std::getline(file, line))
	{
		size_t i = line.find("//");
		if (i != std::string::npos)
			line.resize(i);

		if (line.empty())
			continue;

		// 각 파일 데이터 읽기
		std::filesystem::path path;
		path = std::filesystem::current_path() / "map_datas" / "stage" / line;
		bool LoadStageData(std::ifstream& file);
		if (!FileRead(path, LoadStageData))
			return false;

		// 불안한 코드
		path.replace_extension() += "_bg";
		path.replace_extension(".txt");
		if (!FileRead(path, LoadBGData, stage_datas[stage_datas.size() - 1].bg))
			stage_datas[stage_datas.size() - 1].bg = nullptr;
	}
	
	return true;
}

bool LoadStageData(std::ifstream& file)
{
	stage_datas.push_back({});
	size_t current_stage_index = stage_datas.size() - 1;

	std::string line;
	char id = 0;
	IntVec2 player_init_position = { -1, -1 };

	while (std::getline(file, line))
	{
		size_t i = line.find("//");
		if (i != std::string::npos)
			line.resize(i);

		if (line.empty())
			continue;

		size_t index = line.find("=");
		if (index != std::string::npos)
		{
			std::string key(line.data(), index);
			std::string value(line.data() + index + 1, line.size() - index - 1);

			if (key == "id")
			{
				if (value.empty())
				{
					Log("Not found id value.\n");
					return false;
				}

				id = value[0];
				continue;
			}
			else if (key == "player_init_position")
			{
				index = line.find(',');
				if (index == std::string::npos)
				{
					Log("Not found position.\n");
					return false;
				}

				std::string left(line.data(), index);
				std::string right(line.data() + index + 1, line.size() - index - 1);

				if (left.empty() || right.empty())
				{
					Log("Not found position value.\n");
					return false;
				}

				int x = stoi(left);
				int y = stoi(right);

				if (x >= console_size.x || x < 0)
				{
					Log("Invalid x position value. x:", x, "\n");
					return false;
				}
				if (y >= console_size.y || y < 0)
				{
					Log("Invalid y position value. y:", y, "\n");
					return false;
				}

				IntVec2 position = { x, y };
				stage_datas[stage_datas.size() - 1].player_init_position = position;
				continue;
			}
			
		}

		if (!entity_datas.contains(id))
		{
			Log("Invalid id. id:", id, "\n");
			return false;
		}

		index = line.find(',');
		if (index == std::string::npos)
		{
			Log("Not found position.\n");
			return false;
		}

		std::string left(line.data(), index);
		std::string right(line.data() + index + 1, line.size() - index - 1);

		if (left.empty() || right.empty())
		{
			Log("Not found position value.\n");
			return false;
		}

		int x = stoi(left);
		int y = stoi(right);

		if (x >= console_size.x || x < 0)
		{
			Log("Invalid x position value. x:", x, "\n");
			return false;
		}
		if (y >= console_size.y || y < 0)
		{
			Log("Invalid y position value. y:", y, "\n");
			return false;
		}

		IntVec2 position = { x, y };
		stage_datas[current_stage_index].entity_datas.emplace_back(id, position);
	}

	if (stage_datas[current_stage_index].entity_datas.empty())
	{
		Log("stage in zero entity. stage index:", current_stage_index, "\n");
		return false;
	}

	if (player_init_position == IntVec2{ -1, -1 })
	{
		Log("Not define player init position.\n");
		return false;
	}

	return true;
}