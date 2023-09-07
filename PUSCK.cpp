#include <iostream>
#include "sha1.h"
#include "chat.h"
#include <string.h>
using namespace std;

void throwHere(const std::string & text)
    {
        std::cout << "Throw text: " << text.c_str() << std::endl;
        throw 1;
    }

int main()
{
    
    bool good = false;
    setlocale(LC_ALL, "rus");
    try
    {
        Chat chat;
        chat.start();
        while (chat.isChatWork())
        {
            chat.ShowLoginMenu();
            chat.reg((char*)"user1", (char*)"qwerty12345", sizeof("qwerty12345"));
            if (!chat.login((char*)"user1", (char*)"qwerty12345", sizeof("qwerty12345")))  throwHere ("in c.login() user1");
            
            while (chat.getCurrentUser())
            {
                chat.ShowUserMenu();
            }
        }
        good = true;
    }
    catch (...) {
        good = false;
    }

    if (good) {
        std::cout << "Тесты пройдены" << std::endl;
    }
    else {
        std::cout << "Тесты провалены" << std::endl;
    }
    return 0;
}