#include <iostream>

enum class months {
    Jan = 1,
    Feb,
    Mar,
    Apr,
    May,
    Jun,
    Jul,
    Aug,
    Sep,
    Oct,
    Nov,
    Dec
};

int main()
{
    setlocale(LC_ALL, "Russian");

    int choice = 13;

    while (choice != 0) {

        std::cout << "Введите номер месяца:" << std::endl;
        std::cin >> choice;

        if (choice == 0) { break; };

        months month = static_cast<months>(choice);

        switch (month)
        {
        case (months::Jan):
            std::cout << "Январь - году начало, зиме серёдка." << std::endl;
            break;
        case (months::Feb):
            std::cout << "Февраль - зима с весной встречается впервой." << std::endl;
            break;
        case (months::Mar):
            std::cout << "Март - месяц любит куролесить." << std::endl;
            break;
        case (months::Apr):
            std::cout << "Апрель - воду подбирает, цветы раскрывает." << std::endl;
            break;
        case (months::May):
            std::cout << "Май - леса наряжает, лето в гости ожидает." << std::endl;
            break;
        case (months::Jun):
            std::cout << "Июнь - солнце высоко, с утра до вечера далеко." << std::endl;
            break;
        case (months::Jul):
            std::cout << "Июль - перелом лета, месяц красного цвета." << std::endl;
            break;
        case (months::Aug):
            std::cout << "Август - солнце греет, а вода холодеет." << std::endl;
            break;
        case (months::Sep):
            std::cout << "Сентябрь - красно лето провожает, осень златую встречает." << std::endl;
            break;
        case (months::Oct):
            std::cout << "Октябрь - до обеда осень, после обеда зима." << std::endl;
            break;
        case (months::Nov):
            std::cout << "Ноябрь - месяц перволедья, санного первопутка." << std::endl;
            break;
        case (months::Dec):
            std::cout << "Декабрь - год кончает, зиму начинает." << std::endl;
            break;
        default:
            std::cout << "Неправильное число." << std::endl;
            break;
        }
    }

    std::cout << "До свидания!";
}