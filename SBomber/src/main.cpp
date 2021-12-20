#include "SBomber.h"
#include "MyTools.h"
#include "ScreenSingleton.h"


int main(void) {
  MyTools::OpenLogFile("log.txt");

  SBomber game;
  game.run();

  MyTools::CloseLogFile();

  return 0;
}
