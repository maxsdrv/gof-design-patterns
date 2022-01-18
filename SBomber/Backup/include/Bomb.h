#pragma once

#include "DynamicObject.h"
#include "IVisitor.h"

class Bomb : public DynamicObject
{
public:

	static const uint16_t BombCost = 10; // ��������� ����� � �����

	void Draw() const override;

    void Accept(IVisitor* pVisitor) override;

    ~Bomb() override;
private:

};

