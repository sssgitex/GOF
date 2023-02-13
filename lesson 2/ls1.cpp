#include <iostream>
#include "afactory.h"
#include "command.h"

int main()
{
        // Game game;
        // RomanArmyFactory ra_factory;
        // CarthaginianArmyFactory ca_factory;

        // Army* pRomanArmy = game.createArmy(ra_factory);
        // pRomanArmy -> info();

        // Army* pCarthaginianArmy = game.createArmy(ca_factory);
        // pCarthaginianArmy -> info();

    char s = '1';
    int line;
    std::string str;
    Invoker inv;
    while (s != 'e') // Если не выход
    {
        std::cout << "What to do: " << std::endl
        << "1.Add a line" << std::endl
        << "2.Undo last command" << std::endl
        << "3. Press 'e' to exit" << std::endl;
        std::cin >> s;
        switch (s)
        {
            case '1':
                std::cout << "What line to insert: ";
                std::cin >> line;
                --line;
                std::cout << "What to insert: ";
                std::cin >> str;
                inv.Insert(line, str);
                break;
            case '2':
                inv.Undo();
                break;
        }
        std::cout << "$$$DOCUMENT$$$" << std::endl;
        inv.Show();
        std::cout << "$$$DOCUMENT$$$" << std::endl;
        
    }
    return 0;
}