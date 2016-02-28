#ifndef SRC_LOG_H_
#define SRC_LOG_H_

#include <cstdio>
#include <cstdarg>

class Log
{
public:
	static Log* getInstance();
	~Log();

	enum debugLevelType
	{
		ERROR_LEVEL,
		WARNING_LEVEL,
		INFO_LEVEL,
		DEBUG_LEVEL,
		TRACE_LEVEL
	};

	void write(debugLevelType debug_level, const char* str, ...);

	char* generateLogFilename();
	void generateTimestamp(char* str, size_t len);

private:
	Log();
	static Log* INSTANCE;

	FILE* log_file;
	char filename[80];

	static const bool PRINT_TO_DS;
};

#endif /* SRC_LOG_H_ */
