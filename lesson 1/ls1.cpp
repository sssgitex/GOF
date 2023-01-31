#include <iostream>
//#include "solid.h"
#include <vector>
#include "singleton.h"
#include "proxy.h"
#include <thread>
#include <mutex>

std::mutex m1;

void func1(){
    m1.lock();
    Singleton* s1 = Singleton::GetInstance("value1");
    std::cout << s1->getValue();
    m1.unlock();
}

void func2(){
    m1.lock();
    Singleton* s2 = Singleton::GetInstance("value2");
    std::cout << s2->getValue();
    m1.unlock();
}

int main() {

    // std::vector<L::Employee*> employees;
    // employees.push_back(new L::JuniorEmployee);
    // employees.push_back(new L::SeniorEmployee);

    /*std::vector<L::IEmployee*> employeesData;
    std::vector<L::IWork*> employeesWork;

    employeesData.push_back(new L::JuniorEmployee);
    employeesData.push_back(new L::SeniorEmployee);

    employeesWork.push_back(new L::SeniorEmployee);


    for (auto data: employeesData){
        std::cout << data->GetEmployeeDetails() << std::endl;
    }

    for (auto data: employeesWork){
        std::cout << data->GetWorkDetails() << std::endl;
    }

    // for(auto employee: employees){
    //     std::cout << employee->GetWorkerDetails() << std::endl;
    // }*/

    std::thread t1(func1);
    std::thread t2(func2);

    t1.join();
    t2.join();

    File* file = new File;
    ProxyFile* proxyFile = new ProxyFile(file);
    proxyFile->write();

    return 0;
}