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
    std::string get_city() {
        return city;
    }
    std::string get_street() {
        return street;
    }
    int get_house() {
        return house;
    }
    int get_appartment() {
        return appartment;
    }

    std::string get_output_address() {
        return city + ", " + street + ", " + std::to_string(house) + ", " + std::to_string(appartment) + "\n";
    }
};

void sort(Address* addresses, int size) {
    
    bool flag = true;
    Address temp;
    
    do {
        flag = false;
        
        for (int i = 0; i <= size - 2; ++i) {
            for (int j = i + 1; j <= size - 1; ++j) {
                if (addresses[i].get_city() > addresses[j].get_city()) {
                    temp.set_address(addresses[i].get_city(), addresses[i].get_street(), addresses[i].get_house(), addresses[i].get_appartment());
                    addresses[i].set_address(addresses[j].get_city(), addresses[j].get_street(), addresses[j].get_house(), addresses[j].get_appartment());
                    addresses[j].set_address(temp.get_city(), temp.get_street(), temp.get_house(), temp.get_appartment());
                    flag = true;
                }
            }
        }
    } while (flag);
}

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
    }

    file_in.close();

    sort(addresses, N);

    std::string* string_addresses = new std::string[N];

    for (int i = 0; i < N; ++i) {
        string_addresses[i] = addresses[i].get_output_address();
    }

    std::ofstream file_out("out.txt");

    if (!file_out.is_open()) {
        std::cout << "Не получилось открыть файл out.txt\n";
        return 1;
    }

    file_out << N << "\n";
    for (int i = 0; i < N; ++i) {
        file_out << string_addresses[i];
    }

    file_out.close();

    delete[] addresses;
    delete[] string_addresses;
}
