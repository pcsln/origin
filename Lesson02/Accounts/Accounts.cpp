#include <iostream>
#include <Windows.h>

struct accounts {
    long int bank_account;
    std::string name;
    double balance;
};

void create_account(accounts* account) {
    std::cout << "Введите номер счета: ";
    std::cin >> account->bank_account;
    std::cout << "Введите имя владельца: ";
    std::cin >> account->name;
    std::cout << "Введите баланс: ";
    std::cin >> account->balance;
    std::cout << std::endl;
}

void change_account(accounts* account, double balance) {
    account->balance = balance;
}

void print_account(accounts* account) {
    std::cout << "Ваш счёт: " << account->name << ", " << account->bank_account << ", " << account->balance << std::endl;
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    accounts account = { 0, "", 0 };

    create_account(&account);

    double balance = 0;
    std::cout << "Введите новый баланс: ";
    std::cin >> balance;
    std::cout << std::endl;

    change_account(&account, balance);

    print_account(&account);

}
