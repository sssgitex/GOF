#pragma once

#include <vector>
#include "DynamicObject.h"
#include "BombObserver.h"
#include "DestroyableGroundObject.h"

class Bomb : public DynamicObject, public Lesson_05::ISubject
{
public:

	static const uint16_t BombCost = 10; // the cost of the bomb in points scored

	void Draw() const override;

    void Report(Lesson_05::IEventLogger *) override;

    void AddObserver(DestroyableGroundObject *) override;

    void RemoveObserver(DestroyableGroundObject *) override;

    optional<DestroyableGroundObject *> CheckDestoyableObjects() override;

private:
    vector <DestroyableGroundObject*> observers;
};

namespace Lesson_02
{
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
}
