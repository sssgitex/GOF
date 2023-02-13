#pragma once

#include <stdint.h>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

namespace MyTools {

    // Color palette from 0 to 15
    enum ConsoleColor
    {
        CC_Black = 0,
        CC_Blue,
        CC_Green,
        CC_Cyan,
        CC_Red,
        CC_Magenta,
        CC_Brown,
        CC_LightGray,
        CC_DarkGray,
        CC_LightBlue,
        CC_LightGreen,
        CC_LightCyan,
        CC_LightRed,
        CC_LightMagenta,
        CC_Yellow,
        CC_White
    };

    string GetCurDateTime();

	//=============================================================================================


    class ScreenSingleton
    {
    public:

        static ScreenSingleton& getInstance()
        {
            static ScreenSingleton _instance;
            return _instance;
        }
        void ClrScr();
        void __fastcall GotoXY(double x, double y);
        uint16_t GetMaxX();
        uint16_t GetMaxY();
        void SetColor(ConsoleColor color);

        ~ScreenSingleton() = default;

    private:

        ScreenSingleton() = default;
        ScreenSingleton(const ScreenSingleton& root) = delete;
        ScreenSingleton& operator=(const ScreenSingleton&) = delete;
    }; 


    class ILogger
    {
    public:

        virtual void OpenLogFile(const string&) = 0;
        virtual void CloseLogFile() = 0;
        virtual void WriteToLog(const string&) = 0;
        virtual void WriteToLog(const string&, int) = 0;
        virtual void WriteToLog(const string&str, double) = 0;

        ILogger() = default;
        virtual ~ILogger() = default;
    };

    class FileLoggerSingleton: public ILogger
    {
    public:

        static FileLoggerSingleton& getInstance()
        {
            static FileLoggerSingleton _instance;
            return _instance;
        };

        ofstream& getLogOut();

        void __fastcall OpenLogFile(const string&) override;
        void CloseLogFile() override;
        void __fastcall WriteToLog(const string&) override;
        void __fastcall WriteToLog(const string&, int) override;
        void __fastcall WriteToLog(const string&, double) override;

        ~FileLoggerSingleton() = default;

    private:

        FileLoggerSingleton() = default;
        FileLoggerSingleton(const FileLoggerSingleton&) = delete;
        FileLoggerSingleton& operator=(const FileLoggerSingleton&) = delete;
        FileLoggerSingleton& operator=(FileLoggerSingleton&&) = delete;

        ofstream logOut;
    }; 

    class LoggerSingleton: public ILogger
    {
    public:
        static LoggerSingleton& getInstance()
        {
            static LoggerSingleton _instance;
            return _instance;
        };

        void __fastcall OpenLogFile(const string&) override;
        void CloseLogFile() override;
        void __fastcall WriteToLog(const string&) override;
        void __fastcall WriteToLog(const string&, int) override;
        void __fastcall WriteToLog(const string&, double) override;

    private:
        LoggerSingleton() : _logger (FileLoggerSingleton::getInstance()), count (0) {};

        LoggerSingleton(const LoggerSingleton&) = delete;
        LoggerSingleton& operator=(const LoggerSingleton&) = delete;
        LoggerSingleton& operator=(LoggerSingleton&&) = delete;

        FileLoggerSingleton&_logger;
        unsigned long count;
    }; 

}; 