#include "File.h"

char* LoadBGData(std::ifstream& file)
{
	char* new_bg = nullptr;
	new_bg = static_cast<char*>(malloc(console_size.x * console_size.y));
	if (!new_bg)
	{
		Log("Buffer Allocate Fail.\n");
		return nullptr;
	}

	std::string line;
	char default_char = ' ';

	std::getline(file, line);
	size_t index = line.find('=');
	if (index != std::string::npos)
	{
		std::string_view key(line.data(), index);
		std::string_view value(line.data() + index + 1, line.size() - (index + 1));
		if (key == "default_char")
		{
			if (!value.empty())
			{
				default_char = value[0];
				Log("Set default character = ", default_char, "\n");
			}
			else
			{
				Log("Invalid value.\n");
			}
		}
		else
		{
			Log("Unknown data.\n");
		}
	}

	size_t lineCount = 0;

	while (std::getline(file, line))
	{
		if (line.length() > console_size.x)
		{
			Log("The width is too large.\nline : ", lineCount + 1, ", length : ", line.length(), '\n');
			free(new_bg);
			return nullptr;
		}

		if (lineCount >= console_size.y)
		{
			Log("The height is too high.\nline : ", lineCount + 1, ", length : ", line.length(), '\n');
			free(new_bg);
			return nullptr;
		}

		size_t prevLength = line.length();
		if (line.length() < console_size.x)
			line.resize(console_size.x, default_char);

		Log("line ");
		if (lineCount < 10)
			Log('0');
		if (lineCount < 100)
			Log('0');
		Log(lineCount, ":", line, ": length ", prevLength, '\n');

		memcpy(new_bg + (lineCount * console_size.x), line.c_str(), line.size());

		++lineCount;
	}

	if (lineCount < console_size.y)
	{
		memset(new_bg + (lineCount * console_size.x), default_char, (console_size.y - lineCount) * console_size.x);
		line = {};
		line.resize(console_size.x, default_char);
		while (lineCount < console_size.y)
		{
			Log("line ");
			if (lineCount < 10)
				Log('0');
			if (lineCount < 100)
				Log('0');
			Log(lineCount, ":", line, ": length 0\n");
			++lineCount;
		}
	}

	return new_bg;
}