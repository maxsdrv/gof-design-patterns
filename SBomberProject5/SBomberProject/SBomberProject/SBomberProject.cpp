
#include <conio.h>

#include "SBomber.h"
#include "MyTools.h"
#include "FileLoggerSingletone.h"
#include "FileLoggerProxy.h"

using namespace std;

//========================================================================================================================

int main(void)
{
    FileLoggerProxy::getInstance().OpenLogFile("log.txt");
    
    SBomber game;

    do {
        game.TimeStart();
        //начало отсчёта времени до начала операции
        GetCurDateTimeSingletone::getInstance().Start();
        if (_kbhit())
        {
            game.ProcessKBHit();
        }

        ScreenSingleton::getInstance().ClrScr();

        game.DrawFrame();
        game.MoveObjects();
        game.CheckObjects();

        game.TimeFinish();
        //сохраняем значение времени конца операции
        GetCurDateTimeSingletone::getInstance().SaveTime();

    } while (!game.GetExitFlag());

    FileLoggerProxy::getInstance().CloseLogFile();
   
    //Выво в консоль среднего значения времени логирования
    std::cout << "   Result of logging \t";
    std::cout << GetCurDateTimeSingletone::getInstance().Calculating();
    std::cout << "\n";

    return 0;
}
