#include "FileLoggerProxy.h"


void FileLoggerProxy::OpenLogFile(const std::string& FN)
{
	logOut.open(FN, std::ios_base::out);
}

void FileLoggerProxy::CloseLogFile()
{
	if (logOut.is_open())
	{
		logOut.close();
	}
}

void FileLoggerProxy::WriteToLog(const std::string& str)
{
	if (logOut.is_open()) {
		logOut << GetCurDateTimeSingletone::getInstance().GetCurDateTime() <<
			" - " << str << " Proxy" << std::endl;
	}
}

void FileLoggerProxy::WriteToLog(const std::string& str, int n)
{
	if (logOut.is_open()) {
		logOut << GetCurDateTimeSingletone::getInstance().GetCurDateTime() <<
			" - " << str << n << " Proxy" << std::endl;
	}
}

void FileLoggerProxy::WriteToLog(const std::string& str, double d)
{
	if (logOut.is_open()) {
		logOut << GetCurDateTimeSingletone::getInstance().GetCurDateTime() <<
			" - " << str << d << " Proxy" << std::endl;
	}
}
