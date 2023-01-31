#pragma once
#include <iostream>

class Singleton{
private:
    std::string _value;
    Singleton(const std::string& value): _value(value){}
    static Singleton* _singleton;

public:
    static Singleton* GetInstance(const std::string& value);
    Singleton(Singleton& other) = delete;
    void operator = (const Singleton&) = delete;

    std::string getValue() const {return _value;}
};
    Singleton *Singleton::GetInstance(const std::string &value) {
        if(_singleton == nullptr){
            _singleton = new Singleton(value);
        }
        return _singleton;
    }

    Singleton* Singleton::_singleton = nullptr;
