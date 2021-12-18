#pragma once

#include "IFileLogger.h"
#include "GetCurDateTimeSingletone.h"
#include "FileLoggerSingletone.h"

class FileLoggerProxy : public FileLoggerSingletone
{
public:
	static FileLoggerProxy& getInstance() {
		static FileLoggerProxy theInstance;
		return theInstance;
	}
	void OpenLogFile(const std::string& FN);
	void CloseLogFile();
	void WriteToLog(const std::string& str);
	void WriteToLog(const std::string& str, int n);
	void WriteToLog(const std::string& str, double d);
private:
	FileLoggerProxy() {}
	~FileLoggerProxy() {}
	FileLoggerProxy(const FileLoggerProxy& root) = delete;
	FileLoggerProxy& operator=(const FileLoggerProxy&) = delete;
	FileLoggerProxy(FileLoggerProxy&& root) = delete;
	FileLoggerProxy& operator=(FileLoggerProxy&&) = delete;
};

