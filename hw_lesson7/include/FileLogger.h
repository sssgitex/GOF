#ifndef FILE_LOGGER
#define FILE_LOGGER

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

    class FileLogger {
        ofstream logOut;

        void __fastcall OpenLogFile(const string &);

        void CloseLogFile();

    public:
        FileLogger();

        ~FileLogger();

        void __fastcall WriteToLog(const string &);

        void __fastcall WriteToLog(const string &, int);

        void __fastcall WriteToLog(const string &, double);

    };

    extern FileLogger logger;


#endif //FILE_LOGGER
