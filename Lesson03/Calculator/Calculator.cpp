#include <iostream>

class Calculator {
private:
    double num1;
    double num2;
public:
    double add() {
        return num1 + num2;
    }
    double multiply() {
        return num1 * num2;
    }
    double subtract_1_2() {
        return num1 - num2;
    }
    double subtract_2_1() {
        return num2 - num1;
    }
    double divide_1_2() {
        return num1 / num2;
    }
    double divide_2_1() {
        return num2 / num1;
    }
    bool set_num1(double num1) {
        if (num1 == 0) {
            std::cout << "Неверный ввод!" << std::endl;
            return false;
        }
        else {
            this->num1 = num1;
            return true;
        }
    }
    bool set_num2(double num2) {
        if (num2 == 0) {
            std::cout << "Неверный ввод!" << std::endl;
            return false;
        }
        else {
            this->num2 = num2;
            return true;
        }
    }
};

int main()
{
    setlocale(LC_ALL, "Russian");

    double number;
    
    Calculator Calc;

    while (true) {

        do {
            std::cout << "Введите num1: ";
            std::cin >> number;
        } while (!Calc.set_num1(number));
        
        do {
            std::cout << "Введите num2: ";
            std::cin >> number;
        } while (!Calc.set_num2(number));

        std::cout << "num1 + num2 = " << Calc.add() << std::endl;
        std::cout << "num1 * num2 = " << Calc.multiply() << std::endl;
        std::cout << "num1 - num2 = " << Calc.subtract_1_2() << std::endl;
        std::cout << "num2 - num1 = " << Calc.subtract_2_1() << std::endl;
        std::cout << "num1 / num2 = " << Calc.divide_1_2() << std::endl;
        std::cout << "num2 / num1 = " << Calc.divide_2_1() << std::endl;
    }

}
