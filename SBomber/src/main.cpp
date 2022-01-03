#include "SBomber.h"
#include "TestFileLogger.h"


int main(int argc, char** argv) {
  FileLoggerProxy::getInstance().OpenLogFile("log.txt");
  TestFileLogger::getInstance().OpenLogFile("test_log.txt");

  SBomber game;
  game.run();

  FileLoggerProxy::getInstance().CloseLogFile();
  TestFileLogger::getInstance().CloseLogFile();

  return 0;
}
