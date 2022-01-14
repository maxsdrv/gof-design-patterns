#pragma once

#include "DestroyableGroundObject.h"
#include "HouseBuilderA.h"
#include <cstdint>

class House : public DestroyableGroundObject {
public:
  bool isInside(double x1, double x2) const override;

  inline uint16_t GetScore() const override {
    return score;
  }

  void Draw() const override;

private:
  const uint16_t score = 40;
  char look[7][14]; 
  friend class HouseBuilderA;
};


