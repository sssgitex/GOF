
#include <conio.h>
#include <windows.h>
#include <stdint.h>
#include <time.h>
#include <chrono>
#include <iomanip>

#include "include/MyTools.h"

using namespace std;

namespace MyTools
{
    string GetCurDateTime()
    {
        auto cur = chrono::system_clock::now();
        time_t time = chrono::system_clock::to_time_t(cur);
        char buf[64] = { 0 };
        ctime_s(buf, 64, &time);
        buf[strlen(buf) - 1] = '\0';
        return string(buf);
    } 

    //=============================================================================================



    void ScreenSingleton::ClrScr()
    {
        system("cls");
    } 

    void __fastcall ScreenSingleton::GotoXY(double x, double y)
    {
        const COORD cc = { short(x), short(y) };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cc);
    } 

    uint16_t ScreenSingleton::GetMaxX()
    {
        HANDLE hWndConsole;
        if (hWndConsole = GetStdHandle(-12))
        {
            CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
            if (GetConsoleScreenBufferInfo(hWndConsole, &consoleInfo))
            {
                return consoleInfo.srWindow.Right;
                int height = consoleInfo.srWindow.Bottom - consoleInfo.srWindow.Top + 1;
            }
        }

        return 0;
    } 

    uint16_t ScreenSingleton::GetMaxY()
    {
        HANDLE hWndConsole;
        if (hWndConsole = GetStdHandle(-12))
        {
            CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
            if (GetConsoleScreenBufferInfo(hWndConsole, &consoleInfo))
            {
                return consoleInfo.srWindow.Bottom;
            }
        }

        return 0;
    } 

    void ScreenSingleton::SetColor(ConsoleColor color)
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, color); 
    } 

    //=============================================================================================


    void __fastcall FileLoggerSingleton::OpenLogFile(const string &FN)
    {
        logOut.open(FN, ios_base::out);
    } 

    void FileLoggerSingleton::CloseLogFile()
    {
        if (logOut.is_open())
            logOut.close();
    } 

    void __fastcall FileLoggerSingleton::WriteToLog(const string &str)
    {
        if (logOut.is_open())
            logOut << GetCurDateTime() << " - " << str << endl;
    } 
    void __fastcall FileLoggerSingleton::WriteToLog(const string &str, int n)
    {
        if (logOut.is_open())
            logOut << GetCurDateTime() << " - " << str << n << endl;
    } 

    void __fastcall FileLoggerSingleton::WriteToLog(const string &str, double d)
    {
        if (logOut.is_open())
            logOut << GetCurDateTime() << " - " << str << d << std::endl;
    } 

    ofstream& FileLoggerSingleton::getLogOut() {
        return logOut;
    } 



    void __fastcall LoggerSingleton::OpenLogFile(const string &FN)
    {
        _logger.OpenLogFile(FN);
    } 

    void LoggerSingleton::CloseLogFile()
    {
        _logger.CloseLogFile();
    } 

    void __fastcall LoggerSingleton::WriteToLog(const string &str)
    {
        _logger.getLogOut() << setfill('0') << setw(9) << ++count << '.';
        _logger.WriteToLog(str);;
    } 

    void __fastcall LoggerSingleton::WriteToLog(const string &str, int n)
    {
        _logger.getLogOut() << setfill('0') << setw(9) << ++count << '.';
        _logger.WriteToLog(str, n);;
    } 

    void __fastcall LoggerSingleton::WriteToLog(const string &str, double d)
    {
        _logger.getLogOut() << setfill('0') << setw(9) << ++count << '.';
        _logger.WriteToLog(str, d);
    } 


    //=============================================================================================


};