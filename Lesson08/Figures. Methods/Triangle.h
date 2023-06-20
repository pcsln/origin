#pragma once
#include "Figure.h"

class Triangle : public Figure {
protected:
    unsigned int side_a;
    unsigned int side_b;
    unsigned int side_c;
    unsigned short angle_A;
    unsigned short angle_B;
    unsigned short angle_C;
public:
    Triangle(unsigned int a, unsigned int b, unsigned int c, unsigned short A, unsigned short B, unsigned short C);
    unsigned int get_side_a();
    unsigned int get_side_b();
    unsigned int get_side_c();
    unsigned short get_angle_A();
    unsigned short get_angle_B();
    unsigned short get_angle_C();
    void print() override {
        std::cout << name << " (Стороны " << side_a << ", " << side_b << ", " << side_c << "; Углы ";
        std::cout << angle_A << ", " << angle_B << ", " << angle_C << ") создан." << std::endl;
        std::cout << std::endl;
    }
};