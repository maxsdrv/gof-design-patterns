#pragma once

#include <vector>

#include "LevelGUI.h"
#include "Plane.h"
#include "Bomb.h"
#include "Ground.h"
#include "Tank.h"
#include "House.h"
#include "FileLoggerProxy.h"

class SBomber
{
public:

    SBomber();
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

private:

    void CheckPlaneAndLevelGUI();
    void CheckBombsAndGround();
    void  CheckDestroyableObjects(Bomb* pBomb);

    void  DeleteDynamicObj(DynamicObject * pBomb);
    void  DeleteStaticObj(GameObject* pObj);

    Ground * FindGround() const;
    Plane * FindPlane() const;
    LevelGUI * FindLevelGUI() const;
    std::vector<DestroyableGroundObject*> FindDestroyableGroundObjects() const;
    std::vector<Bomb*> FindAllBombs() const;

    void DropBomb();

    std::vector<DynamicObject*> vecDynamicObj;
    std::vector<GameObject*> vecStaticObj;
    
    bool exitFlag;

    uint64_t startTime, finishTime, passedTime;
    uint16_t bombsNumber, deltaTime, fps;
    int16_t score;
};