#pragma once
#include <iostream>

class Fraction
{
private:
	int numerator_;
	int denominator_;
public:
	Fraction(int numerator, int denominator);
	std::string print();
	Fraction operator+(Fraction other);
	Fraction operator-(Fraction other);
	Fraction operator*(Fraction other);
	Fraction operator/(Fraction other);
	Fraction operator-();
	Fraction operator++();
	Fraction operator++(int);
	Fraction operator--();
	Fraction operator--(int);
	bool operator==(Fraction other);
	bool operator!=(Fraction other);
	bool operator<(Fraction other);
	bool operator>(Fraction other);
	bool operator>=(Fraction other);
	bool operator<=(Fraction other);
	int gcd(int a, int b);
	void reduce();
};