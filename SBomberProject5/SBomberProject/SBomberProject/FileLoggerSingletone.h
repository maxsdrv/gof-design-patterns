#pragma once

#include <string>
#include <fstream>

class FileLoggerSingletone 
{
public:
	std::ofstream logOut;

	static FileLoggerSingletone& getInstance() {
		static FileLoggerSingletone theInstance;
		return theInstance;
	}

	void OpenLogFile(const std::string& FN);
	void CloseLogFile();
    void WriteToLog(const std::string& str);
	void WriteToLog(const std::string& str, int n);
	void WriteToLog(const std::string& str, double d);
protected:
	FileLoggerSingletone() {}
	~FileLoggerSingletone() {}
	FileLoggerSingletone(const FileLoggerSingletone& root) = delete;
	FileLoggerSingletone& operator=(const FileLoggerSingletone&) = delete;
	FileLoggerSingletone(FileLoggerSingletone&& root) = delete;
	FileLoggerSingletone& operator=(FileLoggerSingletone&&) = delete;
};

