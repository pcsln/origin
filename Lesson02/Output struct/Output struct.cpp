#include <iostream>
#include <Windows.h>

struct address {
    std::string city;
    std::string street;
    int house;
    int appartment;
    int index;
};

void output_structure(address office) {
     std::cout << "Город: " << office.city << std::endl;
     std::cout << "Улица: " << office.street << std::endl;
     std::cout << "Номер дома: " << office.house << std::endl;
     std::cout << "Номер квартиры: " << office.appartment << std::endl;
     std::cout << "Индекс: " << office.index << std::endl;
     std::cout << std::endl;
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int N = 4;

    address* offices = new address[N];

    offices[0] = { "Ульяновск", "Карла Маркса", 33, 29, 432700 };
    offices[1] = { "Ульяновск", "Строителей", 12, 25, 432013 };
    offices[2] = { "Новоульяновск", "Заводская", 1, 4, 433234 };
    offices[3] = { "Димитровград", "Циолковского", 54, 544, 435019 };

    for (int i = 0; i < N; ++i) {
        output_structure(offices[i]);
    }
    
    delete[] offices;
}