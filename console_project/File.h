#pragma once
#include <filesystem>
#include <fstream>
#include "LogHelper.h"
#include "ConsoleDatas.h"

template <typename Func>
bool FileRead(const std::filesystem::path& path, Func work)
{
	std::ifstream fileReader(path);
	Log("Reading file... : ", path, '\n');

	if (!fileReader)
	{
		Log("not found file.", '\n');
		return false;
	}
	else if (!work(fileReader))
	{
		Log("file read fail.", '\n');
		return false;
	}

	Log("file read Success.", '\n');
	return true;
}

template <typename Func, typename Result>
bool FileRead(const std::filesystem::path& path, Func work, Result& result)
{
	std::ifstream fileReader(path);
	Log("Reading file... : ", path, '\n');

	if (!fileReader)
	{
		Log("not found file.", '\n');
		return false;
	}
	result = work(fileReader);
	if (!result)
	{
		Log("file read fail.", '\n');
		return false;
	}

	Log("file read Success.", '\n');
	return true;
}

char* LoadBGData(std::ifstream& file);