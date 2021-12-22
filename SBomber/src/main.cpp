#include "SBomber.h"
#include "MyTools.h"
#include "ScreenSingleton.h"
#include "WinterPlane.h"
#include "GetCurDateTimeSingleton.h"


int main(void) {
  FileLoggerProxy::getInstance().OpenLogFile("log.txt");

  SBomber game;
  game.run();

  FileLoggerProxy::getInstance().CloseLogFile();

  return 0;
}
