#pragma once

#include "DynamicObject.h"

class Bomb : public DynamicObject
{
public:

	static const uint16_t BombCost = 10; // the cost of the bomb in points scored

	void Draw() const override;

private:

};

class BombDecorator: public DynamicObject
{
private:
    DynamicObject *bomb;

public:
    BombDecorator(DynamicObject *_bomb) : bomb(_bomb)
    {};
    ~BombDecorator () = default;

    void Move(uint16_t time) override;
    void Draw() const override;

};