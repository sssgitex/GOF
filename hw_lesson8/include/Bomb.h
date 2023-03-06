#pragma once

#include "DynamicObject.h"

class Bomb : public DynamicObject
{
public:
    Bomb() = default;
    ~Bomb() = default;

    Bomb(const Bomb& );

	static const uint16_t BombCost = 10;

	void Draw() const override;

    Bomb* clone() const
    {
        return new Bomb(*this);
    };

private:

};

