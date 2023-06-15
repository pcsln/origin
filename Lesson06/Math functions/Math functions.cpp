#include <iostream>
#include <Windows.h>
#include "Math.h"

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int N = 1;
    int M = 1;
    int code = 1;

    while (true) {
        std::cout << "Введите первое число: ";
        std::cin >> N;
        std::cout << "Введите второе число: ";
        std::cin >> M;
        std::cout << "Выберите операцию (1 - сложение, 2 - вычитание, 3 - умножение, 4 - деление, 5 - возведение в степень): ";
        std::cin >> code;

        switch (code)
        {
        case (1):
            std::cout << "N + M = " << add(N, M) << std::endl;
            break;
        case (2):
            std::cout << "N - M = " << sub(N, M) << std::endl;
            break;
        case (3):
            std::cout << "N * M = " << mult(N, M) << std::endl;
            break;
        case (4):
            std::cout << "N / M = " << division(N, M) << std::endl;
            break;
        case (5):
            std::cout << "N в степени M равно " << power(N, M) << std::endl;
            break;
        default:
            std::cout << "До свидания!";
                return 1;
        }
    }
}