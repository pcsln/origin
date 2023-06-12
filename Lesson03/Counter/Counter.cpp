#include <iostream>
#include <Windows.h>

class Counter {
private:
    int count;
public:
    Counter() {
        this->count = 1;
    }
    Counter(int value) {
        this->count = value;
    }
    void inc() {
        this->count++;
    }
    void dec() {
        this->count--;
    }
    void print() {
        std::cout << this->count << std::endl;
    }
};

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
 
    std::string initial_value_code = "";
    int initial_value = 0;
    
    std::cout << "Вы хотите указать начальное значение счётчика? Введите да или нет: ";
    std::cin >> initial_value_code;

    Counter* Count;
    
    if (initial_value_code != "да") {
        Count = new Counter();
    }
    else {
        std::cout << "Введите начальное значение счётчика: ";
        std::cin >> initial_value;
        Count = new Counter(initial_value);
    }
 
    std::string command = "";

    while (true) {
        std::cout << "Введите команду ('+', '-', '=' или 'x'): ";
        std::cin >> command;

        if (command == "+") {
            Count->inc();
            continue;
        }
        else if (command == "-") {
            Count->dec();
            continue;
        }
        else if (command == "=") {
            Count->print();
            continue;
        }
        else if (command == "х") {
            std::cout << "До свидания!";
            delete Count;
            return 1;
        }
        else {
            std::cout << "Неверная команда." << std::endl;
        }
    }
}