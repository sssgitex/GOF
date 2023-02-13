#pragma once
#include <iostream>
#include <vector>

class Document{
private:
    std::vector<std::string> data;
public:
    Document() {
        data.resize(100);
    }

    void Insert(int line, std::string& str){
        if(line <= data.size()){
            data.insert(data.begin() + line, str);
        }
        else{
            std::cerr << "Error!" << std::endl;
        }
    }

    void Remove(int line){
        if(line <= data.size() && line > 0){
            data.erase(data.begin() + line);
        }
        else{
            std::cerr << "Error!" << std::endl;
        }
    }

    void Show(){
        for (int i = 0; i < data.size(); ++i){
            std::cout << i+1 << ". " << data[i] << std:: endl;
        }
    }
};

class Command{
protected:
    Document* doc;
public:
    virtual void Execute() = 0;
    virtual void UnExecute() = 0;
    virtual ~Command(){};

    void setDoc(Document *newDoc) {
        doc = newDoc;
    }
};

class InsertCommand: public Command{
private:
    int line;
    std::string str;
public:
    InsertCommand(int line, const std::string &str) : line(line), str(str) {}

    void Execute() override {
        doc->Insert(line, str);
    }
    void UnExecute() override {
        doc->Remove(line);
    }
};

class Invoker{
private:
    std::vector<Command*> doneCommands;
    Document doc;
    Command* pCommand;
public:
    Invoker() : pCommand(nullptr) {}
    Invoker(Command *pCommand) : pCommand(pCommand) {}

    virtual ~Invoker() {
        for(Command* ptr : doneCommands){
            delete ptr;
        }
    }

    void Insert(int line , std::string& str){
        pCommand = new InsertCommand(line, str);
        pCommand->setDoc(&doc);
        pCommand->Execute();
        doneCommands.push_back(pCommand);
    }

    void Undo(){
        if(doneCommands.size() != 0){
            pCommand = doneCommands.back();
            doneCommands.pop_back();
            pCommand->UnExecute();
            delete pCommand;
        }
        else{
            std::cout << "Nothing to undo" << std::endl;
        }
    }

    void Show(){
        doc.Show();
    };
};