#pragma once
#include "Figure.h"

class Quadrangle : public Figure {
public:
    unsigned int side_a;
    unsigned int side_b;
    unsigned int side_c;
    unsigned int side_d;
    unsigned short angle_A;
    unsigned short angle_B;
    unsigned short angle_C;
    unsigned short angle_D;
    Quadrangle(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned short A, unsigned short B, unsigned short C, unsigned short D);
    unsigned int get_side_a();
    unsigned int get_side_b();
    unsigned int get_side_c();
    unsigned int get_side_d();
    unsigned short get_angle_A();
    unsigned short get_angle_B();
    unsigned short get_angle_C();
    unsigned short get_angle_D();
    void print() override {
        std::cout << name << " (Стороны " << side_a << ", " << side_b << ", " << side_c << ", " << side_d << "; Углы ";
        std::cout << angle_A << ", " << angle_B << ", " << angle_C << ", " << angle_D << ") создан." << std::endl;
        std::cout << std::endl;
    }
};