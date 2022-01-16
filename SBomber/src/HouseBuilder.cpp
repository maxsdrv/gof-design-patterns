#include "HouseBuilder.h"

HouseBuilder::~HouseBuilder() {
    delete pHouse;
}


HouseBuilder::HouseBuilder() : pHouse(nullptr) {
}