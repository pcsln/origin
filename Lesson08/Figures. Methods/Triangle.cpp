#include "Triangle.h"
#include "IncorrectFigure.h"

Triangle::Triangle(unsigned int a, unsigned int b, unsigned int c, unsigned short A, unsigned short B, unsigned short C) {

    if (A + B + C != 180) {
        throw IncorrectFigure("Ошибка создания треугольной фигуры. Сумма углов не равна 180 \n");
    }

    this->side_a = a;
    this->side_b = b;
    this->side_c = c;
    this->angle_A = A;
    this->angle_B = B;
    this->angle_C = C;

    this->sides_count = 3;
}
unsigned int Triangle::get_side_a() {
    return side_a;
}
unsigned int Triangle::get_side_b() {
    return side_b;
}
unsigned int Triangle::get_side_c() {
    return side_c;
}
unsigned short Triangle::get_angle_A() {
    return angle_A;
}
unsigned short Triangle::get_angle_B() {
    return angle_B;
}
unsigned short Triangle::get_angle_C() {
    return angle_C;
}