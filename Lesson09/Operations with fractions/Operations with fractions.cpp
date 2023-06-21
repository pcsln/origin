#include <iostream>
#include <string>
#include <Windows.h>
#include "Fraction.h"

int main()
{

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int f_numerator = 1;
	int f_denominator = 1;

	std::cout << "Введите числитель первой дроби: ";
	std::cin >> f_numerator;

	do {
		std::cout << "Введите ненулевой знаменатель первой дроби: ";
		std::cin >> f_denominator;
	} while (f_denominator == 0);
	
	Fraction f1(f_numerator, f_denominator);
	f1.reduce();
	
	std::cout << "Введите числитель второй дроби: ";
	std::cin >> f_numerator;

	do {
		std::cout << "Введите ненулевой знаменатель второй дроби: ";
		std::cin >> f_denominator;
	} while (f_denominator == 0);
	
	Fraction f2(f_numerator, f_denominator);
	f2.reduce();
	
	Fraction f3 = f1 + f2;
	f3.reduce();
	std::cout << f1.print() << " + " << f2.print() << " = " << f3.print() << std::endl;

	f3 = f1 - f2;
	f3.reduce();
	std::cout << f1.print() << " - " << f2.print() << " = " << f3.print() << std::endl;

	f3 = f1 * f2;
	f3.reduce();
	std::cout << f1.print() << " * " << f2.print() << " = " << f3.print() << std::endl;

	f3 = f1 / f2;
	f3.reduce();
	std::cout << f1.print() << " / " << f2.print() << " = " << f3.print() << std::endl;

	std::cout << "++" << f1.print() << " * " << f2.print() << " = ";
	f3 = ++f1 * f2;
	f3.reduce();
	std::cout << f3.print() << std::endl;
	std::cout << "Значение дроби 1: " << f1.print() << std::endl;

	std::cout << f1.print() << "-- * " << f2.print() << " = ";
	f3 = f1-- * f2;
	f3.reduce();
	std::cout << f3.print() << std::endl;
	std::cout << "Значение дроби 1: " << f1.print() << std::endl;

	return 0;
}
