
#ifndef BOMB_OBSERVER_H
#define BOMB_OBSERVER_H

#include <iostream>
#include <optional>


class DestroyableGroundObject;

using namespace std;

namespace Lesson_05
{
    class IObserver
    {
    public:
        
        virtual bool HandleInsideCheck (double, double) const = 0;
    };

    class ISubject
    {
    public:
        virtual void AddObserver (DestroyableGroundObject *) = 0; 
        virtual void RemoveObserver (DestroyableGroundObject *) = 0;
        virtual optional <DestroyableGroundObject*> CheckDestoyableObjects() = 0;
    };
}

#endif
