#include "Fraction.h"
#include <string>

Fraction::Fraction(int numerator, int denominator)
{
	numerator_ = numerator;
	denominator_ = denominator;
}

std::string Fraction::print() {
	return std::to_string(numerator_) + "/" + std::to_string(denominator_);
}

Fraction Fraction::operator+(Fraction other) {
	return Fraction((numerator_ * other.denominator_) + (denominator_ * other.numerator_), denominator_ * other.denominator_);
}
Fraction Fraction::operator-(Fraction other) {
	return Fraction((numerator_ * other.denominator_) - (denominator_ * other.numerator_), denominator_ * other.denominator_);
}
Fraction Fraction::operator*(Fraction other) {
	return Fraction(numerator_ * other.numerator_, denominator_ * other.denominator_);
}
Fraction Fraction::operator/(Fraction other) {
	return Fraction(numerator_ * other.denominator_, denominator_ * other.numerator_);
}
Fraction Fraction::operator-() {
	return Fraction(-numerator_, denominator_);
}

Fraction Fraction::operator++() {
	numerator_ = numerator_ + denominator_;
	return *this;
}
Fraction Fraction::operator++(int) {
	Fraction temp = *this;
	++(*this);
	return temp;
}
Fraction Fraction::operator--() {
	numerator_ = numerator_ - denominator_;
	return *this;
}
Fraction Fraction::operator--(int) {
	Fraction temp = *this;
	--(*this);
	return temp;
}

bool Fraction::operator==(Fraction other) {
	return (numerator_ / denominator_) == (other.numerator_ / other.denominator_);
}
bool Fraction::operator!=(Fraction other) {
	return !(*this == other);
}
bool Fraction::operator<(Fraction other) {
	return (numerator_ / denominator_) < (other.numerator_ / other.denominator_);
}
bool Fraction::operator>(Fraction other) {
	return other < *this;
}
bool Fraction::operator>=(Fraction other) {
	return !(*this < other);
}
bool Fraction::operator<=(Fraction other) {
	return !(*this > other);
}
int Fraction::gcd(int a, int b) {
	while (b > 0) {
		int c = a % b;
		a = b;
		b = c;
	}
	return a;
}
void Fraction::reduce() {
	int gcd = this->gcd(abs(numerator_), denominator_);
	if (gcd != 1) {
		numerator_ = numerator_ / gcd;
		denominator_ = denominator_ / gcd;
	}
}