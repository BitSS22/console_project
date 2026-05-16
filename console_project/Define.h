#pragma once

#define LOG
#define CONSOLE_LOG

#define MAX_ENTITY_COUNT 100
#define MAX_PLAYER_BULLET_COUNT 4

#define COUNT_OF_SECOND 1000
#define TARGET_FRAME 50

#ifdef LOG
	#ifdef CONSOLE_LOG
		#define LOG_OSTREAM std::cout
	#else
		#define LOG_OSTREAM logger_stream
	#endif
#endif