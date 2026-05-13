#include "Time.h"
#include <Windows.h>
#include "ConsoleDatas.h"

unsigned long long prev_time = 0;

void TimeInit()
{
	prev_time = static_cast<unsigned long long>(timeGetTime()) - target_delta_time;
}

void AsyncFrame()
{
	// 1. 현재 시간 가져오기
	// 2. 이전 시간에 비해 얼마나 경과했는지 비교하기
	// 3. 목표 프레임에 비해 너무 많으면 sleep으로 대기
	// 4. 목표 프레임 만큼 현재 시간 증가
	// 게임 내 독자적인 시간을 가진다.
	// 내 세상의 시간은 이래.

	int now_time = static_cast<unsigned long long>(timeGetTime());
	int used_time = now_time - prev_time;

	if (used_time < target_delta_time)
	{
		Sleep(target_delta_time - used_time);
	}

	prev_time += target_delta_time;
}