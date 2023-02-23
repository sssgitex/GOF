#pragma once

#include <stdint.h>
#include <string>

namespace MyTools {

    // ������� ������ �� 0 �� 15
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

	//=============================================================================================
    class ScreenSingleton
    {
    public:
        static ScreenSingleton& getInstance(){
            static ScreenSingleton theInstance;
            return theInstance;
        }

    void ClrScr();

	void __fastcall GotoXY(double x, double y);

	uint16_t GetMaxX();

	uint16_t GetMaxY();

    void SetColor(ConsoleColor color);

    private:
        ScreenSingleton(){}
        ScreenSingleton(const ScreenSingleton& root) = delete;
        ScreenSingleton& operator=(const ScreenSingleton&) = delete;
    };

	

	//=============================================================================================
    class FileLoggerSingletone{
    private:
        FileLoggerSingletone(){}
        FileLoggerSingletone(const FileLoggerSingletone& root) = delete;
        FileLoggerSingletone& operator=(const FileLoggerSingletone&) = delete;
    public:
        static FileLoggerSingletone& getInstance()
        {
            static FileLoggerSingletone theInstance;
            return theInstance;
        }

        void __fastcall OpenLogFile(const std::string& FN);

        void CloseLogFile();

        void __fastcall WriteToLog(const std::string& str);

        void __fastcall WriteToLog(const std::string& str, int n);

        void __fastcall WriteToLog(const std::string& str, double d);
    };

    class IFileLoggerSingletone{
    public:
        virtual void OpenLogFile(const std::string& FN) = 0;
        virtual void CloseLogFile() = 0;
        virtual void WriteToLog(const std::string& str) = 0;
        virtual void WriteToLog(const std::string& str, int n) = 0;
        virtual void WriteToLog(const std::string& str, double d) = 0;
    };

    class proxyLoggerSingleton: IFileLoggerSingletone{
    private:
        proxyLoggerSingleton(){}
        proxyLoggerSingleton(const proxyLoggerSingleton& root) = delete;
        proxyLoggerSingleton& operator=(const proxyLoggerSingleton&) = delete;
        int num = 0;
    public:
        void __fastcall OpenLogFile(const std::string& FN) override {
            logOut.open(FN, ios_base::out);
        };

        void CloseLogFile() override{
            if (logOut.is_open())
            {
                logOut.close();
            }
        };

        void __fastcall WriteToLog(const std::string& str) override{
            if (logOut.is_open())
            {
                logOut << num++;
                logOut << GetCurDateTime() << " - " << str << endl;
            }
        };

        void __fastcall WriteToLog(const std::string& str, int n) override{
            if (logOut.is_open())
            {
                logOut << num++;
                logOut << GetCurDateTime() << " - " << str << n << endl;
            }
        };

        void __fastcall WriteToLog(const std::string& str, double d) override{
            if (logOut.is_open())
            {
                logOut << num++;
                logOut << GetCurDateTime() << " - " << str << d << endl;
            }
        };
    };
	

	//=============================================================================================

};