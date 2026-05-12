#pragma once
#include <ostream>

template <typename Text>
concept can_out_stream = requires(std::ostream& stream, Text&& data)
{
	stream << data;
};

#ifdef LOG
template <can_out_stream... Text>
void Log(Text&&... arg)
{
	(LOG_OSTREAM << ... << std::forward<Text>(arg));
}
#else
#define Log(NOTHING)
#endif