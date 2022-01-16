//Homework 4 
Task 1.
Create Builder
//****************************************************//


#pragma once

#include <memory>

#include "House.h"

class HouseBuilder {
public:
    virtual ~HouseBuilder() = default;
    HouseBuilder() = default;
    virtual void createHouse() {};
    virtual void createWall() {};
    virtual void createWindow() {};
    virtual void createPipe() {};
    virtual void createRoof() {};
    virtual House* getHouse() {return pHouse;}
    virtual void printHouse() {};
protected:
	std::unique_ptr<House> pHouse;
};




#pragma once

#include "HouseBuilder.h"

class HouseBuilderA : public HouseBuilder {
public:
    void createHouse() override;
    void createWall() override;
    void createWindow() override;
    void createPipe() override;
    void createRoof() override;
    void printHouse() override;
private:
};


#include <iostream>

#include "HouseBuilderA.h"


void HouseBuilderA::createWall() {
    for (size_t i = 0; i < House::rows; ++i) {
        for (size_t j = 0; j < House::columns; ++j) {
            if ((i == 5 && j == 4) || (i == 6 && j == 4)) {
                pHouse->look[i][j] = '#';
            }
            else if ((i == 5 && j == 12) || (i == 6 && j == 12)) {
                pHouse->look[i][j] = '#';
            }
        }
    }

}

void HouseBuilderA::createWindow() {
    for (size_t i = 0; i < House::rows; ++i) {
        for (size_t j = 0; j < House::columns; ++j) {
            if (i == 5 && j == 7) {
                while (j <= 9) {
                    pHouse->look[i][j] = '#';
                    ++j;
                }
            }
            else if (i == 6 && j == 7) {
                while (j <= 9) {
                    pHouse->look[i][j] = '#';
                    ++j;
                }
            }
        }
    }
}

void HouseBuilderA::createPipe() {
    for (size_t i = 0; i < House::rows; ++i) {
        for (size_t j = 0; j < House::columns; ++j) {
            if (i == 0 && j == 10) {
                pHouse->look[i][j] = '#';
            }
            else if (i == 1 && j == 10) {
                pHouse->look[i][j] = '#';
            }
            else if (i == 2 && j == 10) {
                pHouse->look[i][j] = '#';
            }
        }
    }
}

void HouseBuilderA::createRoof() {
    for (size_t i = 0; i < House::rows; ++i) {
        for (size_t j = 0; j < House::columns; ++j) {
            if (i == 1 && j == 8) {
                pHouse->look[i][j] = '#';
            }
            else if ((i == 2 && j == 7) || (i == 2 && j == 9)) {
                pHouse->look[i][j] = '#';
            }
            else if ((i == 3 && j == 6) || (i == 3 && j == 10)) {
                pHouse->look[i][j] = '#';
            }
            else if (i == 4 && j == 4) {
                while (j <= 12) {
                    pHouse->look[i][j] = '#';
                    ++j;
                }
            }
        }
    }
}

void HouseBuilderA::printHouse() {
    for (size_t i = 0; i < House::rows; ++i) {
        for (size_t j = 0; j < House::columns; ++j) {
            std::cout << pHouse->look[i][j] << ' ';
        }
        std::cout << '\n';;
    }

}

void HouseBuilderA::createHouse() {
    pHouse = std::make_unique<House>();
    for (size_t i = 0; i < House::rows; ++i) {
        for (size_t j = 0; j < House::columns; ++j) {
            pHouse->look[i][j] = ' ';
        }
    }
}


#ifndef SBOMBER_DIRECTOR_H
#define SBOMBER_DIRECTOR_H

#include "HouseBuilder.h"
#include "HouseBuilderA.h"
#include "House.h"

class Director {
public:
    House* createStandardHouse(HouseBuilder* pBuilder) {
        pBuilder->createHouse();
        pBuilder->createPipe();
        pBuilder->createRoof();
        pBuilder->createWall();
        pBuilder->createWindow();
        return (pBuilder->getHouse());
    }
    House* createMinimalHouse(HouseBuilder* pBuilder) {
        pBuilder->createHouse();
        pBuilder->createRoof();
        pBuilder->createWall();
        return (pBuilder->getHouse());

    }
private:
};


#endif //SBOMBER_DIRECTOR_H


//*********************************************************************************//
Task 2.
Bridge Pattern.

#pragma once

#include "Command.h"

class Command;

class CollisionDetector {
public:
    CollisionDetector(const std::vector<GameObject*>& vecStaticObj,
                      const std::vector<DynamicObject*>& vecDynamicObj,
                      int16_t score, bool exitFlag);

    void CheckPlaneAndLevelGUI();
    void CheckBombsAndGround();
    void  CheckDestroyableObjects(Bomb* pBomb);
    static void CommandExecute(Command* command);

    Ground * FindGround() const;
    Plane * FindPlane() const;
    LevelGUI * FindLevelGUI() const;
    [[nodiscard]] std::vector<DestroyableGroundObject*> FindDestroyableGroundObjects() const;
    std::vector<Bomb*> FindAllBombs() const;
private:
    int16_t m_score;
    bool m_exitFlag;
    std::vector<GameObject*> m_vecStaticObj;
    std::vector<DynamicObject*> m_vecDynamicObj;
};




#include "CollisionDetector.h"
#include "BombIterator.h"
#include "OddBombIterator.h"

CollisionDetector::CollisionDetector(const std::vector<GameObject*>& vecStaticObj,
                                     const std::vector<DynamicObject*>& vecDynamicObj, int16_t score,
                                     bool exitFlag) :
        m_vecStaticObj(vecStaticObj), m_vecDynamicObj(vecDynamicObj), m_score(score), m_exitFlag(exitFlag) {}




void CollisionDetector::CheckPlaneAndLevelGUI() {
    if (FindPlane()->GetX() > FindLevelGUI()->GetFinishX()) {
        m_exitFlag = true;
    }
}

void CollisionDetector::CheckBombsAndGround() {
    Ground *pGround = FindGround();
    const double y = pGround->GetY();
    //Using Iterator pattern
    std::vector<Bomb *> vecBombs = FindAllBombs();
    auto *pItr = new BombIterator(vecBombs);

    for (pItr->begin(); !pItr->isDone(); pItr->Next()) {
        if (pItr->CurrentObj()->GetY() >= y) {
            pGround->AddCrater(pItr->CurrentObj()->GetX());
            CheckDestroyableObjects(pItr->CurrentObj());
            auto command = std::make_unique<DeleteDynamicObj>();
            //Using Command pattern
            command->setParam(pItr->CurrentObj(), m_vecDynamicObj);
            CommandExecute(command.get());
        }
    }
    delete pItr;
}

void CollisionDetector::CheckDestroyableObjects(Bomb* pBomb) {
    std::vector<DestroyableGroundObject *> vecDestroyableObjects =
            FindDestroyableGroundObjects();
    const double size = pBomb->GetWidth();
    const double size_2 = size / 2;
    for (size_t i = 0; i < vecDestroyableObjects.size(); i++) {
        const double x1 = pBomb->GetX() - size_2;
        const double x2 = x1 + size;
        if (vecDestroyableObjects[i]->isInside(x1, x2)) {
            m_score += vecDestroyableObjects[i]->GetScore();
            //Using Command pattern
            auto command = std::make_unique<DeleteStaticObj>();
            command->setParam(vecDestroyableObjects[i], m_vecStaticObj);
            CommandExecute(command.get());
        }
    }
}

void CollisionDetector::CommandExecute(Command *command) {
    command->execute();
}



Ground *CollisionDetector::FindGround() const {
    Ground *pGround;

    for (size_t i = 0; i < m_vecStaticObj.size(); i++) {
        pGround = dynamic_cast<Ground *>(m_vecStaticObj[i]);
        if (pGround != nullptr) {
            return pGround;
        }
    }

    return nullptr;
}

Plane *CollisionDetector::FindPlane() const {
    for (size_t i = 0; i < m_vecDynamicObj.size(); i++) {
        Plane *p = dynamic_cast<Plane *>(m_vecDynamicObj[i]);
        if (p != nullptr) {
            return p;
        }
    }

    return nullptr;
}

LevelGUI *CollisionDetector::FindLevelGUI() const {
    for (size_t i = 0; i < m_vecStaticObj.size(); i++) {
        LevelGUI *p = dynamic_cast<LevelGUI *>(m_vecStaticObj[i]);
        if (p != nullptr) {
            return p;
        }
    }

    return nullptr;
}

std::vector<DestroyableGroundObject *> CollisionDetector::FindDestroyableGroundObjects() const {
    std::vector<DestroyableGroundObject *> vec;
    Tank *pTank;
    House *pHouse;
    for (size_t i = 0; i < m_vecStaticObj.size(); i++) {
        pTank = dynamic_cast<Tank *>(m_vecStaticObj[i]);
        if (pTank != nullptr) {
            vec.push_back(pTank);
            continue;
        }

        pHouse = dynamic_cast<House *>(m_vecStaticObj[i]);
        if (pHouse != nullptr) {
            vec.push_back(pHouse);
            continue;
        }
    }

    return vec;
}

std::vector<Bomb *> CollisionDetector::FindAllBombs() const {
    std::vector<Bomb *> vecBombs;
    std::unique_ptr<IIterator> pItr;
    pItr = std::make_unique<OddBombIterator>(m_vecDynamicObj);

    for (pItr->First(); !pItr->isDone(); pItr->Next()) {
        Bomb *pBomb = pItr->CurrentObj();
        if (pBomb != nullptr) {
            vecBombs.push_back(pBomb);
        }
    }

    return vecBombs;
}


//*******************************************************************************//
SBomber after changes

#pragma once

class SBomber
{
public:

    explicit SBomber(int type_house);
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
    House* createHouse(const double pos, const uint16_t width) const;

    static void CommandExecute(Command* command);
private:
    void updateFromCommand(Context* context);

    std::vector<DynamicObject*> vecDynamicObj;
    std::vector<GameObject*> vecStaticObj;

    bool exitFlag;
    bool oddIteration; // for Pattern Iterator, switching between Odd or Even Iteration

    uint64_t startTime, finishTime, passedTime;
    uint16_t bombsNumber, deltaTime, fps;
    int16_t score;

    int m_type_house; // for Pattern Builder.
    std::unique_ptr<CollisionDetector> m_CollisionD;//for Pattern Bridge
};



House *SBomber::createHouse(const double pos, const uint16_t width) const {
    const uint16_t maxY = ScreenSingleton::getInstance().GetMaxY();
    const uint16_t groundY = maxY - 5;

    //Builder Pattern
    House* pHouse = nullptr;
    if (m_type_house == 1) {
        Director dir{};
        HouseBuilder* standardHouse = new HouseBuilderA;
        pHouse = dir.createStandardHouse(standardHouse);
        pHouse->SetWidth(width);
        pHouse->SetPos(pos, groundY - 1);
    }
    else if (m_type_house == 2) {
        Director dir{};
        HouseBuilder* minimalHouse = new HouseBuilderA;
        pHouse = dir.createMinimalHouse(minimalHouse);
        pHouse->SetWidth(width);
        pHouse->SetPos(pos, groundY - 1);
    }


    return pHouse;
}

SBomber::SBomber(int type_house)
        : exitFlag(false), startTime(0), finishTime(0), deltaTime(0), passedTime(0),
          fps(0), bombsNumber(10), score(0), oddIteration(false), m_type_house(type_house) {
    FileLoggerProxy::getInstance().WriteToLog(std::string(__func__)
                                              + " was invoked");

    vecDynamicObj.push_back(createPlane());
    vecStaticObj.push_back(createUI(passedTime, fps, bombsNumber, score));
    vecStaticObj.push_back(createGround());
    vecStaticObj.push_back(createTank(30, 13));
    vecStaticObj.push_back(createTank(50, 13));
    vecStaticObj.push_back(createHouse(80, 13));

    m_CollisionD = std::make_unique<CollisionDetector>(vecStaticObj, vecDynamicObj, score, exitFlag);
}


void SBomber::CheckObjects() {
    FileLoggerProxy::getInstance().WriteToLog(std::string(__func__)
                                              + " was invoked");
    m_CollisionD->CheckPlaneAndLevelGUI();
    m_CollisionD->CheckBombsAndGround();
};


void SBomber::ProcessKBHit() {
    int c = getchar();

    if (c == 224) {
        c = getchar();
    }

    FileLoggerProxy::getInstance().WriteToLog(std::string(__func__)
                                              + " was invoked. key = ", c);

    //Creating Command
    auto context = std::make_unique<Context>();
    auto command = std::make_unique<CommandDropBomb>();

    Plane *plane = m_CollisionD->FindPlane();
    context->setParam(plane, vecDynamicObj, bombsNumber, 2,
                      SMALL_CRATER_SIZE, score);
    command->setParam(context.get());

    switch (c) {

        case 27: // esc
            exitFlag = true;
            break;

        case 72: // up
            m_CollisionD->FindPlane()->ChangePlaneY(-0.25);
            break;

        case 80: // down
            m_CollisionD->FindPlane()->ChangePlaneY(0.25);
            break;

        case 'b':
            CommandExecute(command.get());
            updateFromCommand(context.get());
            break;

        case 'B':
            CommandExecute(command.get());
            updateFromCommand(context.get());
            break;

        default:
            break;
    }
}

void SBomber::DrawFrame() {
    FileLoggerProxy::getInstance().WriteToLog(std::string(__func__)
                                              + " was invoked");
    for (size_t i = 0; i < vecDynamicObj.size(); i++) {
        if (vecDynamicObj[i] != nullptr) {
            vecDynamicObj[i]->Draw();
        }
    }

    for (size_t i = 0; i < vecStaticObj.size(); i++) {
        if (vecStaticObj[i] != nullptr) {
            vecStaticObj[i]->Draw();
        }
    }

    ScreenSingleton::getInstance().GotoXY(0, 0);
    fps++;

    m_CollisionD->FindLevelGUI()->SetParam(passedTime, fps, bombsNumber, score);
}




//****************************************************************************//
main.cpp

#include "SBomber.h"
#include "TestFileLogger.h"
#include "Director.h"


int main(int argc, char** argv) {
  FileLoggerProxy::getInstance().OpenLogFile("log.txt");
  TestFileLogger::getInstance().OpenLogFile("test_log.txt");

	std::cout << "Choose house type: \n" << "1: Standard house.\n" << "2: Minimal house.\n";
	int c;
	std::cin >> c;

  SBomber game(c);
  game.run();

  FileLoggerProxy::getInstance().CloseLogFile();
  TestFileLogger::getInstance().CloseLogFile();


  return 0;
}








