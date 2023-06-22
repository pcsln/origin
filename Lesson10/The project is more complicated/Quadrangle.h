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
        std::cout << name << std::endl;
        std::cout << "Стороны: а=" << get_side_a() << " b=" << get_side_b() << " c=" << get_side_c() << " d=" << get_side_d() << std::endl;
        std::cout << "Углы: A=" << get_angle_A() << " B=" << get_angle_B() << " C=" << get_angle_C() << " D=" << get_angle_D() << std::endl;
        std::cout << std::endl;
    }
};