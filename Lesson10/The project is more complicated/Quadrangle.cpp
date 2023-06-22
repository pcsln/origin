#include "Quadrangle.h"

Quadrangle::Quadrangle(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned short A, unsigned short B, unsigned short C, unsigned short D) {
    this->side_a = a;
    this->side_b = b;
    this->side_c = c;
    this->side_d = d;
    this->angle_A = A;
    this->angle_B = B;
    this->angle_C = C;
    this->angle_D = D;

    this->sides_count = 4;
}
unsigned int Quadrangle::get_side_a() {
    return side_a;
}
unsigned int Quadrangle::get_side_b() {
    return side_b;
}
unsigned int Quadrangle::get_side_c() {
    return side_c;
}
unsigned int Quadrangle::get_side_d() {
    return side_d;
}
unsigned short Quadrangle::get_angle_A() {
    return angle_A;
}
unsigned short Quadrangle::get_angle_B() {
    return angle_B;
}
unsigned short Quadrangle::get_angle_C() {
    return angle_C;
}
unsigned short Quadrangle::get_angle_D() {
    return angle_D;
}