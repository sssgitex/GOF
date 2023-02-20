#pragma once

#include <stdint.h>
#include <vector>

#include "DestroyableGroundObject.h"

class House : public DestroyableGroundObject
{
public:

	bool __fastcall isInside(double x1, double x2) const override;

	inline uint16_t GetScore() const override { return score; }

	void Draw() const override;

	virtual void info() const
    {
        cout << "house" << endl;
    };

private:

	const uint16_t score = 40;
};

 class GreenHouse : public House
    {
    public:

        void Draw() const override;

        void info() const override
        {
            cout << "green house" << endl;
        };

    };

    class RedHouse : public House {
    public:

        void Draw() const override;

        void info() const override
        {
            cout << "red house" << endl;
        };
    };

    class City
    {
        std::vector<House *> buildings;

        virtual ~City()
        {
            for (const auto &_build: buildings)
                delete _build;
        };

        void info() const
        {
            for (const auto &_build: buildings)
                _build->info();
        };
    };

    class CityBuilder
    {
    protected:
        City *city;

    public:
        CityBuilder() : city(nullptr) {};

        virtual ~CityBuilder()
        {
            if (city)
                delete city;
        };

        virtual void CreateCity() {};

        virtual void BuildRedHouse() {};

        virtual void BuildGreenHouse() {};

        virtual City *GetCity() { return city; };
    };

    class RedCityBuilder : public CityBuilder
    {
    public:
        void CreateCity() override
        {
            if (city)
                delete city;

            city = new City;
        };

        void BuildRedHouse() override
        {
            city->buildings.emplace_back(new RedHouse);
        };

    };

    class GreenCityBuilder : public CityBuilder
    {
    public:
        void CreateCity() override
        {
            if (city)
                delete city;

            city = new City;
        };

        void BuildGreenHouse() override
        {
            city->buildings.emplace_back(new GreenHouse);
        };

    };

    class Supervisor
    {
    public:
        City *CreateCity(CityBuilder &builder)
        {
            builder.CreateCity();
            builder.BuildRedHouse();
            builder.BuildGreenHouse();
            
            return builder.GetCity();
        };
    };

    void BuildExample ();
