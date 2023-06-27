#include <iostream>
#include "Greeter.h"
#include "Leaver.h"
#include <Windows.h>

int main()
{

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::string name = "";
    std::cout << "Введите имя: ";
    std::cin >> name;

    Greeter greet;

    std::cout << greet.greet(name) << std::endl << std::endl;

    Leaver leave;

    std::cout << leave.leave(name);


}

