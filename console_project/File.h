#pragma once
#include <filesystem>
#include <fstream>
#include "LogHelper.h"

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
	return true;
}