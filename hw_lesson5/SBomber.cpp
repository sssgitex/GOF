
#include <conio.h>
#include <windows.h>

#include "include/MyTools.h"
#include "include/SBomber.h"
#include "include/House.h"

using namespace std;
using namespace MyTools;

SBomber::SBomber()
    : exitFlag(false),
    startTime(0),
    finishTime(0),
    deltaTime(0),
    passedTime(0),
    fps(0),
    bombsNumber(10),
    score(0)
{
    LoggerSingleton::getInstance().WriteToLog(string(__FUNCTION__) + " was invoked");

    Plane* p = new Plane;
    p->SetDirection(1, 0.1);
    p->SetSpeed(4);
    p->SetPos(5, 10);
    vecDynamicObj.push_back(p);

    AbstractLevelGUI* pGUI = new LevelGUI_1;
    pGUI->SetParam(passedTime, fps, bombsNumber, score);
    const uint16_t maxX = ScreenSingleton::getInstance().GetMaxX();
    const uint16_t maxY = ScreenSingleton::getInstance().GetMaxY();
    const uint16_t offset = 3;
    const uint16_t width = maxX - 7;
    pGUI->SetPos(offset, offset);
    pGUI->SetWidth(width);
    pGUI->SetHeight(maxY - 4);
    pGUI->SetFinishX(offset + width - 4);
    vecStaticObj.push_back(pGUI);

    pFactory = new WinterFactory;
    pFactory->CreateLevel1(vecStaticObj);

    pTreeCreator = new (nothrow) TreeCreatorA;

    pCollDetector = new Lesson_04::CollisionDetector (this, &vecDynamicObj, &vecStaticObj);

}

SBomber::~SBomber()
{
    for (size_t i = 0; i < vecDynamicObj.size(); i++)
    {
        if (vecDynamicObj[i] != nullptr)
        {
            delete vecDynamicObj[i];
        }
    }

    for (size_t i = 0; i < vecStaticObj.size(); i++)
    {
        if (vecStaticObj[i] != nullptr)
        {
            delete vecStaticObj[i];
        }
    }

    if (pFactory)
        delete pFactory;

    if (pTreeCreator)
        delete pTreeCreator;

    if (pCollDetector)
        delete pCollDetector;
}

void SBomber::MoveObjects()
{
    LoggerSingleton::getInstance().WriteToLog(string(__FUNCTION__) + " was invoked");

    Lesson_05::MoveEventLogger moveEvent;

    for (size_t i = 0; i < vecDynamicObj.size(); i++)
    {
        if (vecDynamicObj[i] != nullptr)
        {
            vecDynamicObj[i]->Move(deltaTime);
            vecDynamicObj[i]->Report(&moveEvent);
        }
    }
};

void SBomber::CheckObjects()
{
    LoggerSingleton::getInstance().WriteToLog(string(__FUNCTION__) + " was invoked");

    CheckPlaneAndLevelGUI();
    CheckBombsAndGround();
};

void SBomber::CheckPlaneAndLevelGUI()
{
    if (FindPlane()->GetX() > FindLevelGUI()->GetFinishX())
    {
        exitFlag = true;
    }
}

void SBomber::CheckBombsAndGround()
{
    vector<Bomb*> vecBombs = FindAllBombs();
    Ground* pGround = FindGround();
    const double y = pGround->GetY();
    for (size_t i = 0; i < vecBombs.size(); i++)
    {
        if (vecBombs[i]->GetY() >= y) 
        {
         
            {// *** Lesson 05
                pGround->AddCrater(vecBombs[i]->GetX());
                auto DestoyableObject = vecBombs[i]->CheckDestoyableObjects();
                if (DestoyableObject)
                {
                    score += DestoyableObject.value()->GetScore();
                    DeleteStaticObj(DestoyableObject.value());
                }
                DeleteDynamicObj(vecBombs[i]);
            }
        }
    }

}

void SBomber::CheckDestoyableObjects(Bomb * pBomb)
{
    vector<DestroyableGroundObject*> vecDestoyableObjects = FindDestoyableGroundObjects();
    const double size = pBomb->GetWidth();
    const double size_2 = size / 2;
    for (size_t i = 0; i < vecDestoyableObjects.size(); i++)
    {
        const double x1 = pBomb->GetX() - size_2;
        const double x2 = x1 + size;
        if (vecDestoyableObjects[i]->isInside(x1, x2))
        {
            score += vecDestoyableObjects[i]->GetScore();
            DeleteStaticObj(vecDestoyableObjects[i]);
        }
    }
}

void SBomber::DeleteDynamicObj(DynamicObject* pObj)
{
    auto it = vecDynamicObj.begin();
    for (; it != vecDynamicObj.end(); it++)
    {
        if (*it == pObj)
        {
            vecDynamicObj.erase(it);
            break;
        }
    }

    {// *** Lesson 05
        vector<Bomb*> vecBombs = FindAllBombs();
        for (auto& pBomb : vecBombs)
        {
            auto pObserver = dynamic_cast<DestroyableGroundObject*>(pObj);
            if (pObserver)
                pBomb->RemoveObserver(pObserver);
        }
    }

}


void SBomber::CommandExecuter(auto * pCommand)
{
    pCommand->Execute();
    delete pCommand;
}


void SBomber::DeleteStaticObj(GameObject* pObj)
{

    auto it = vecStaticObj.begin();
    for (; it != vecStaticObj.end(); it++)
    {
        if (*it == pObj)
        {
            vecStaticObj.erase(it);
            break;
        }
    }

    {// *** Lesson 05
        vector<Bomb*> vecBombs = FindAllBombs();
        for (auto& pBomb : vecBombs)
        {
            auto pObserver = dynamic_cast<DestroyableGroundObject*>(pObj);
            if (pObserver)
                pBomb->RemoveObserver(pObserver);
        }
    }

}


vector<DestroyableGroundObject*> SBomber::FindDestoyableGroundObjects() const
{
    vector<DestroyableGroundObject*> vec;
    Tank* pTank;
    House* pHouse;
    for (size_t i = 0; i < vecStaticObj.size(); i++)
    {
        pTank = dynamic_cast<Tank*>(vecStaticObj[i]);
        if (pTank != nullptr)
        {
            vec.push_back(pTank);
            continue;
        }

        pHouse = dynamic_cast<House*>(vecStaticObj[i]);
        if (pHouse != nullptr)
        {
            vec.push_back(pHouse);
            continue;
        }
    }

    return vec;
}

Ground* SBomber::FindGround() const
{
    Ground* pGround;

    for (size_t i = 0; i < vecStaticObj.size(); i++)
    {
        pGround = dynamic_cast<Ground *>(vecStaticObj[i]);
        if (pGround != nullptr)
        {
            return pGround;
        }
    }

    return nullptr;
}

vector<Bomb*> SBomber::FindAllBombs()
{
    vector<Bomb*> vecBombs;

    BombIterator it = SBomber::begin();
    for (; it != SBomber::end(); ++it)
        vecBombs.push_back( &(*it) );



    return vecBombs;
}

Plane* SBomber::FindPlane() const
{
    for (size_t i = 0; i < vecDynamicObj.size(); i++)
    {
        Plane* p = dynamic_cast<Plane*>(vecDynamicObj[i]);
        if (p != nullptr)
        {
            return p;
        }
    }

    return nullptr;
}

AbstractLevelGUI* SBomber::FindLevelGUI() const
{
    for (size_t i = 0; i < vecStaticObj.size(); i++)
    {
        LevelGUI_1* p = dynamic_cast<LevelGUI_1*>(vecStaticObj[i]);
        if (p != nullptr)
        {
            return p;
        }
    }

    return nullptr;
}

void SBomber::ProcessKBHit()
{
    int c = _getch();

    if (c == 224)
    {
        c = _getch();
    }

    LoggerSingleton::getInstance().WriteToLog(string(__FUNCTION__) + " was invoked. key = ", c);

    switch (c) {

    case 27: // esc
        exitFlag = true;
        break;

    case 72: // up
        FindPlane()->ChangePlaneY(-0.25);
        break;

    case 80: // down
        FindPlane()->ChangePlaneY(0.25);
        break;

    case 'b':
        DropBomb();
        break;

    case 'B':
        DropBomb();
        break;

    default:
        break;
    }
}

void SBomber::DrawFrame()
{
    LoggerSingleton::getInstance().WriteToLog(string(__FUNCTION__) + " was invoked");

    for (size_t i = 0; i < vecDynamicObj.size(); i++)
    {
        if (vecDynamicObj[i] != nullptr)
        {
            vecDynamicObj[i]->Draw();
        }
    }

    for (size_t i = 0; i < vecStaticObj.size(); i++)
    {
        if (vecStaticObj[i] != nullptr)
        {
            vecStaticObj[i]->Draw();
        }
    }

    ScreenSingleton::getInstance().GotoXY(0, 0);
    fps++;

    FindLevelGUI()->SetParam(passedTime, fps, bombsNumber, score);
}

void SBomber::TimeStart()
{
    LoggerSingleton::getInstance().WriteToLog(string(__FUNCTION__) + " was invoked");
    startTime = GetTickCount64();
}

void SBomber::TimeFinish()
{
    finishTime = GetTickCount64();
    deltaTime = uint16_t(finishTime - startTime);
    passedTime += deltaTime;

    LoggerSingleton::getInstance().WriteToLog(string(__FUNCTION__) + " deltaTime = ", (int)deltaTime);
}

void SBomber::SwitchTree ()
{

    if (pTreeCreator)
    {
        ITreeCreator *newCreator;

        if ( typeid(*pTreeCreator) == typeid(TreeCreatorA) )
            newCreator = new (nothrow) TreeCreatorB;
        else
            newCreator = new (nothrow) TreeCreatorA;

        delete pTreeCreator;
        pTreeCreator = newCreator;
    }
    else
        pTreeCreator = new (nothrow) TreeCreatorA;

}

void SBomber::DropBomb()
{



    if (bombsNumber > 0)
    {
        LoggerSingleton::getInstance().WriteToLog(string(__FUNCTION__) + " was invoked");

        Plane* pPlane = FindPlane();
        double x = pPlane->GetX() + 4;
        double y = pPlane->GetY() + 2;

        Bomb* pBomb = new Bomb;
        pBomb->SetDirection(0.3, 1);
        pBomb->SetSpeed(2);
        pBomb->SetPos(x, y);
        pBomb->SetWidth(SMALL_CRATER_SIZE);

        vecDynamicObj.push_back(pBomb);
        bombsNumber--;
        score -= Bomb::BombCost;

        {   // *** Lesson 05
            vector<DestroyableGroundObject*> vecDestoyableObjects = FindDestoyableGroundObjects();
            for (auto& observer : vecDestoyableObjects)
                pBomb->AddObserver(observer);
        }
    }

}


