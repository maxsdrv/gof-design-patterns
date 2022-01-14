#pragma once

#include <vector>
#include <chrono>
#include <memory>

#include "LevelGUI.h"
#include "Plane.h"
#include "Bomb.h"
#include "Ground.h"
#include "Tank.h"
#include "House.h"
#include "FileLoggerProxy.h"
#include "ScreenSingleton.h"
#include "enums/CraterSize.h"

class Command;
class IContext;
class Context;

class SBomber
{
public:

    explicit SBomber();
    ~SBomber();
    
    inline bool GetExitFlag() const { return exitFlag; }

    void ProcessKBHit();
    void TimeStart();
    void TimeFinish();

    void DrawFrame();
    void MoveObjects();
    void CheckObjects();

    void run();

    //static methods
    static Plane* createPlane();
    static LevelGUI* createUI(const uint64_t passedTime,
                              const uint16_t fps,
                              const uint16_t bombsNumber,
                              const int16_t score);
    static Ground* createGround();
    static Tank* createTank(const double pos, const uint16_t width);
    static House* createHouse(const double pos, const uint16_t width);

    static void CommandExecute(Command* command);
private:

    void CheckPlaneAndLevelGUI();
    void CheckBombsAndGround();
    void  CheckDestroyableObjects(Bomb* pBomb);

    void updateFromCommand(Context* context);

    Ground * FindGround() const;
    Plane * FindPlane() const;
    LevelGUI * FindLevelGUI() const;
    std::vector<DestroyableGroundObject*> FindDestroyableGroundObjects() const;
    std::vector<Bomb*> FindAllBombs() const;


    std::vector<DynamicObject*> vecDynamicObj;
    std::vector<GameObject*> vecStaticObj;
    
    bool exitFlag;
    bool oddIteration; // for Pattern Iterator, switching between Odd or Even Iteration

    uint64_t startTime, finishTime, passedTime;
    uint16_t bombsNumber, deltaTime, fps;
    int16_t score;
};
