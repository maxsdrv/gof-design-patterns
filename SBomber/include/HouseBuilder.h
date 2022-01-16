#pragma once

#include "House.h"

class HouseBuilder {
public:
    virtual ~HouseBuilder();
    HouseBuilder();
    virtual void createHouse() {};
    virtual void createWall() {};
    virtual void createWindow() {};
    virtual void createPipe() {};
    virtual void createRoof() {};
    virtual House* getHouse() {return pHouse;}
    virtual void printHouse() {};
protected:
    House* pHouse;
};