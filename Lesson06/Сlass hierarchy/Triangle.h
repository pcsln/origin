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
        std::cout << name << std::endl;
        std::cout << "Стороны: а=" << get_side_a() << " b=" << get_side_b() << " c=" << get_side_c() << std::endl;
        std::cout << "Углы: A=" << get_angle_A() << " B=" << get_angle_B() << " C=" << get_angle_C() << std::endl;
        std::cout << std::endl;
    }
};