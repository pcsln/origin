#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>

class Address {
private:
    std::string city;
    std::string street;
    int house;
    int appartment;
public:
    Address() {
        this->city = "";
        this->street = "";
        this->house = 0;
        this->appartment = 0;
    }
    void set_address(std::string city, std::string street, int house, int appartment) {
        this->city = city;
        this->street = street;
        this->house = house;
        this->appartment = appartment;
    }
    std::string get_output_address() {
        return city + ", " + street + ", " + std::to_string(house) + ", " + std::to_string(appartment) + "\n";
    }
};

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int N = 0;

    std::ifstream file_in("in.txt");

    if (!file_in.is_open()) {
        std::cout << "Не получилось открыть файл in.txt\n";
        return 1;
    }

    file_in >> N;

    Address* addresses = new Address[N];

    std::string* string_addresses = new std::string[N];

    std::string file_city = "";
    std::string file_street = "";
    int file_house = 0;
    int file_appartment = 0;

    for (int i = 0; i < N; ++i) {
        file_in >> file_city;
        file_in >> file_street;
        file_in >> file_house;
        file_in >> file_appartment;
        
        addresses[i].set_address(file_city, file_street, file_house, file_appartment);

        string_addresses[i] = addresses[i].get_output_address();
    }

    file_in.close();

    std::ofstream file_out("out.txt");

    if (!file_out.is_open()) {
        std::cout << "Не получилось открыть файл out.txt\n";
        return 1;
    }

    file_out << N << "\n";
    for (int i = N - 1; i >= 0; --i) {
        file_out << string_addresses[i];
    }

    file_out.close();

    delete[] addresses;
    delete[] string_addresses;
}
