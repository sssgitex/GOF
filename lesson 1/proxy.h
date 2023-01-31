#pragma once
#include <iostream>

class File{
public:
    void write(){
        std::cout << "File is written" << std::endl;
    }
};

class IFile{
public:
    virtual void write() = 0;
};

class ProxyFile: IFile{
private:
    File* file;
    bool CheckAccess() const {
        std::cout << "Proxy: Check Access" << std::endl;
    }
    void LogChange() {
        std::cout << "Proxy: File changed" << std::endl;
    }
public:
    ProxyFile(File *file) : file(file) {}
    void write() override {
        if(CheckAccess()) {
            file->write();
            LogChange();
        }
    }
};