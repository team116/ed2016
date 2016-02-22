#include <Log.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <WPILib.h>

Log* Log::INSTANCE = nullptr;

const bool Log::PRINT_TO_DS = true;

Log::Log()
{
	char* filepath = generateLogFilename();
	log_file = fopen(filepath, "w");
	time_t current_time;
	time(&current_time);
	fprintf(log_file,"Began logging at %s\n",ctime(&current_time));
	fflush(log_file);
}

Log::~Log()
{
	if(log_file){
		time_t end_time;
		time(&end_time);
		fprintf(log_file,"Stopped logging at %s\n", ctime(&end_time));
		fprintf(log_file,"--------------------------------------------------\n");
		fclose(log_file);
	}
}

const Log::debugLevelType MAXIMUM_DEBUG_LEVEL = Log::TRACE_LEVEL;
//this can be set to the least urgent type of message that we want to log
//for the moment it's at trace so we'll log EVERYTHING

void Log::write(Log::debugLevelType debug_level, const char* str, ...)
{
	if(log_file && (debug_level<=MAXIMUM_DEBUG_LEVEL)){

		char buffer[256];
		va_list args;

		va_start(args,str);
		vsprintf(buffer,str,args);
		va_end(args);

		char timestamp[9];
		generateTimestamp(timestamp, 9);

		fputs(timestamp, log_file);
		fputs("\t", log_file);
		fputs(buffer, log_file);
		fputs("\n", log_file);
		fflush(log_file);

		if(PRINT_TO_DS) {
			switch(debug_level) {
			case Log::ERROR_LEVEL:
				DriverStation::ReportError(buffer);
				break;
			case Log::WARNING_LEVEL:
				DriverStation::ReportError(buffer);
				break;
			}
		}
	}
}

void Log::generateTimestamp(char* str, size_t len)
{
	struct tm* local_time;
	time_t t;
	time(&t);
	local_time = localtime(&t);

	snprintf(str, len, "%02i:%02i:%02i", local_time->tm_hour, local_time->tm_min, local_time->tm_sec);
}

char* Log::generateLogFilename()
{
	const char base[] = "log";
	const char ext[] = ".txt";
	FILE* previous_log_file;

	int file_num = 0;

	while(true){
		sprintf(filename,"/var/volatile/tmp/%s%d%s",base,file_num,ext);

		previous_log_file = fopen(filename,"r");
		if(!previous_log_file){
			break;
		}
		else{
			fclose(previous_log_file);
			file_num++;
		}
	}

	printf("Log File Name = %s\n", filename);
	return filename;
}

Log* Log::getInstance()
{
	if (INSTANCE == nullptr)
	{
		INSTANCE = new Log();
	}
	return INSTANCE;
}
