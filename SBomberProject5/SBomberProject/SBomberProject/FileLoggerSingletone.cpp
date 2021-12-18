#include "FileLoggerSingletone.h"
#include "GetCurDateTimeSingletone.h"


void FileLoggerSingletone::OpenLogFile(const std::string& FN)
{
	logOut.open(FN, std::ios_base::out);
}

void FileLoggerSingletone::CloseLogFile()
{
	if (logOut.is_open())
	{
		logOut.close();
	}
}

void FileLoggerSingletone::WriteToLog(const std::string& str)
{
	if (logOut.is_open()) {
		logOut << GetCurDateTimeSingletone::getInstance().GetCurDateTime() <<
			" - " << str << " Singletone" << std::endl;
	}
}

void FileLoggerSingletone::WriteToLog(const std::string& str, int n)
{
	if (logOut.is_open()) {
		logOut << GetCurDateTimeSingletone::getInstance().GetCurDateTime() <<
			" - " << str << n << " Singletone" << std::endl;
	}
}

void FileLoggerSingletone::WriteToLog(const std::string& str, double d)
{
	if (logOut.is_open()) {
		logOut << GetCurDateTimeSingletone::getInstance().GetCurDateTime() <<
			" - " << str << d << " Singletone" << std::endl;
	}
}
