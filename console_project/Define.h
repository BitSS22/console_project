#pragma once

#define LOG
#define CONSOLE_LOG

#ifdef LOG
	#ifdef CONSOLE_LOG
		#define LOG_OSTREAM std::cout
	#elif FILE_LOG
		#define LOG_OSTREAM logger_stream
	#endif
#endif