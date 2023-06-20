#include <iostream>
#include <Windows.h>

class BadLenght : public std::exception {
public:
    const char* what() const override {
        return "Вы ввели слово запретной длины! До свидания!";
    }
};
int check_length(std::string str, int forbidden_length) {
    if (str.length() == forbidden_length) throw BadLenght();
    return str.length();
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int forbidden_length = 0;
    std::string str = "";

    std::cout << "Введите запретную длину: ";
    std::cin >> forbidden_length;

    while (true) {
        try {
            std::cout << "Введите слово: ";
            std::cin >> str;
            std::cout << "Длина слова \"" << str << "\" равна " << check_length(str, forbidden_length) << std::endl;
        }
        catch (const BadLenght& ex) {
            std::cout << ex.what() << std::endl;
            return 1;
        }
    }
}