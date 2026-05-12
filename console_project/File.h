#pragma once
#include <filesystem>
#include <fstream>
#include "LogHelper.h"

template <typename Func>
bool FileRead(const std::filesystem::path& path, Func work)
{
	std::ifstream fileReader(path);

	if (!fileReader)
	{
		Log("not found file. file path : ", path, '\n');
		return false;
	}
	else if (!work(fileReader))
	{
		Log("file read fail. file path : ", path, '\n');
		return false;
	}
	return true;
}