#ifndef COMMANDS_H
#define COMMANDS_H

#include <iostream> // header in standard library
#include <vector>

#include "include/DynamicObject.h"
#include "include/Plane.h"

using namespace std;


template <class T>
class AbstractCommand
{
protected:
    vector <T*> *vecObj;

public:
    AbstractCommand ()
    : vecObj(nullptr) {};
    virtual ~AbstractCommand () = default;

    void SetVector(vector<T *> *_vecObj)
    {
        AbstractCommand::vecObj = _vecObj;
    };

    virtual void Execute() = 0;
};

template <class T>
class CommandDeleteObj : public AbstractCommand <T>
{
private:
    T *pObj;

public:
    CommandDeleteObj ()
    : AbstractCommand <T> (), pObj (nullptr)
    {};
    ~CommandDeleteObj () = default;

    void SetObject(T *_pObj)
    {
        pObj = _pObj;
    };

    void Execute() override;
};

template<class T>
void CommandDeleteObj<T>::Execute() {

    if (!AbstractCommand <T>::vecObj || !pObj)
        return;

    auto it = AbstractCommand <T>::vecObj->begin();
    for (; it != AbstractCommand <T>::vecObj->end(); it++)
    {
        if (*it == pObj)
        {
            AbstractCommand <T>::vecObj->erase(it);
            break;
        }
    }
};

class CommandDropBomb : public AbstractCommand <DynamicObject>
{
private:
    Plane *pPlane;
    uint16_t bombsNumber;

public:
    CommandDropBomb ()
    : AbstractCommand (), pPlane (nullptr), bombsNumber(0)
    {};
    ~CommandDropBomb () = default;

    void SetPlane(Plane *_pPlane)
    {
        pPlane = _pPlane;
    };

    void SetBombsNumber(const uint16_t &_bombsNumber)
    {
        bombsNumber = _bombsNumber;
    };

    void Execute() override;
};



#endif //COMMANDS_H
