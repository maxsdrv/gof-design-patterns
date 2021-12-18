#pragma once

#include <stdint.h>
#include <string>

enum ConsoleColor
{
    CC_Black = 0,
    CC_Blue,
    CC_Green,
    CC_Cyan,
    CC_Red,
    CC_Magenta,
    CC_Brown,
    CC_LightGray,
    CC_DarkGray,
    CC_LightBlue,
    CC_LightGreen,
    CC_LightCyan,
    CC_LightRed,
    CC_LightMagenta,
    CC_Yellow,
    CC_White
};

class ScreenSingleton {
public:
    static ScreenSingleton& getInstance() {
        static ScreenSingleton theInstance;
        return theInstance;
    }
    
    void ClrScr();
    void GotoXY(double x, double y);
    uint16_t GetMaxX();
    uint16_t GetMaxY();
    void SetColor(ConsoleColor color);

private:
    ScreenSingleton() {}
    ScreenSingleton(const ScreenSingleton& root) = delete;
    ScreenSingleton& operator=(const ScreenSingleton&) = delete;
};