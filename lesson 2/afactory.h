#pragma once
#include <iostream>
#include <vector>


class Archer{
public:
    virtual void info() const = 0;
    virtual ~Archer(){}
};

class Horseman{
public:
    virtual void info() const = 0;
    virtual ~Horseman(){}
}; 

class RomanArcher: public Archer{
public:
    void info() const override {
        std::cout << "RomanArcher" << std::endl;
    }
};

class RomanHorseman: public Horseman{
public:
    void info() const override {
        std::cout << "RomanHorseman" << std::endl;
    }
};

class CarthaginianArcher: public Archer{
public:
    void info() const override {
        std::cout << "CarthaginianArcher" << std::endl;
    }
};

class CarthaginianHorseman: public Horseman{
public:
    void info() const override {
        std::cout << "CarthaginianHorseman" << std::endl;
    }
};

class ArmyFactory{
public:
    virtual Archer* createArcher() = 0;
    virtual Horseman* createHorseman() = 0;
    virtual ~ArmyFactory(){};
};

class RomanArmyFactory: public ArmyFactory{
public:
    Archer *createArcher() override{
        return new RomanArcher;
    }

    Horseman *createHorseman() override{
        return new RomanHorseman;
    }
};

class CarthaginianArmyFactory: public ArmyFactory{
public:
    Archer *createArcher() override{
        return new CarthaginianArcher;
    }

    Horseman *createHorseman() override{
        return new CarthaginianHorseman;
    }
};

class Army{
public:
    std::vector<Archer*> va;
    std::vector<Horseman*> vh;

    void info() const{
        for(const auto& unit: va) unit->info();
        for(const auto& unit: vh) unit->info();
    }

    virtual ~Army(){
        for(const auto& unit: va) delete unit;
        for(const auto& unit: vh) delete unit;
    }
};

class Game{
public:
    Army* createArmy(ArmyFactory& factory){
        Army* p = new Army;
        p->va.push_back(factory.createArcher());
        p->vh.push_back(factory.createHorseman());
        return p;
    }
};