#pragma once
#include <iostream>

namespace S{    // 1

    class Employee{
    
    private:
        int ID;
        std::string FullName;
    
    public:
    
    bool Add(Employee emp) {
        //Добавляем данные сотрудника в БД 
        return true;
    }
    };

    class EmployeeReport{
    public:
        void GenerateReport(Employee em){
            //Генерация отчета по дейтельности сотрудника
        }
    };
}

namespace O{ // 2

    class Employee{
    
    private:
        int ID;
        std::string FullName;
    
    public:
    
    bool Add(Employee emp) {
        //Добавляем данные сотрудника в БД 
        return true;
    }
    };

    class EmployeeReport{
        virtual void GenerateReport(Employee* em) = 0;
    };

    class EmployeeReportCSV : public EmployeeReport{
        void GenerateReport(Employee *em) override {
            //
        }
    };
}

namespace L{
    

    class Employee{
    public:
        virtual std::string GetWorkerDetails() {
            return "Base Work";
        }
        virtual std::string GetEmployeeDetails() {
            return "Base Employee";
        }
        virtual int getId() = 0;
    };


    // class SeniorEmployee: public Employee{
    //     std::string GetWorkerDetails() override {
    //         return "Senior Work";
    //     }
    //     std::string GetEmployeeDetails() override {
    //         return "Senior Details";
    //     }
    //     int getId() override {
    //         return 0;
    //     }
    // };

    
    // class JuniorEmployee: public Employee{
    //     std::string GetWorkerDetails() override {
    //         throw std::invalid_argument("No work data");
    //     }
    //     std::string GetEmployeeDetails() override {
    //         return "Junior Details";
    //     }
    //     int getId() override {
    //         return 0;
    //     }
    // };

    class IEmployee{
    public:
        virtual std::string GetEmployeeDetails() = 0;
    };

    class IWork{
    public:
        virtual std::string GetWorkDetails() = 0;
    };

    class SeniorEmployee: public IEmployee, public IWork{
    public:
        std::string GetEmployeeDetails() override {
            return "Senior details"; 
        }
    
        std::string GetWorkDetails() override {
            return "Senior Work";
        }
    };

    class JuniorEmployee: public IEmployee{
    public:
        std::string GetEmployeeDetails() override {
            return "Senior details"; 
        }
    };

}

namespace I{
    class IEmployee{
    public:
        virtual void AddDetailsEmployee() = 0;
        virtual void ShowDetailsEmployee(int id) = 0;
    };

    class IOperationAdd{
        virtual void AddDetailsEmployee() = 0;
    };
    class IOperationGet{
        virtual void ShowDetailsEmployee (int id) = 0;
    };
}

namespace D{
    class Email{
    public:
        void Send(){
            //код для отправки письма
        }
    };

    // class Messenger{
    // private:
    //     Email* email;
    // public:
    //     Messenger() {
    //         email = new Email();
    //     }

    // void send(){
    //     email->Send();
    // }
    // };

    class IMessenger{
    public:
        virtual void send() = 0; 
    };

    class Messenger : public IMessenger{
    public:
        void send() override {
            //send Email
        }
    };

    class SMS : public IMessenger{
    public:
        void send() override {
            //send SMS
        }
    };

    // 1 constructor
    class Messenger{
    private:
        IMessenger* messenger;
    public:
        Messenger(IMessenger *messenger) : messenger(messenger) {}
        void send(){
            messenger->send();
        }
    };

    // 2 property

    class Messenger2{
    private:
        IMessenger* _messenger;
    public:
        Messenger2() {}
        void setMessenger(IMessenger *messenger){
            _messenger = messenger;
        }

        void send(){
            _messenger->send();
        }
    };

    // 3 method

    class Messenger3{
        public:
            void send(IMessenger *messenger){
                messenger->send();
            }
    };


}