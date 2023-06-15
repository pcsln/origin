#include <iostream>
#include <Windows.h>

class Figure {
protected:
    int sides_count;
    std::string name;
public:
    Figure() {
        this->sides_count = 0;
    }
    int get_sides_count() {
        return sides_count;
    }
    void set_name(std::string name) {
        this->name = name;
    }
    std::string get_name() {
        return name;
    }
    virtual bool check() {
        if (sides_count == 0) return true;
        else return false;
    }
    virtual void print() {
        std::cout << get_name() << std::endl;
        check() ? std::cout << "Правильная \n" : std::cout << "Неправильная \n";
        std::cout << "Количество сторон: " << get_sides_count() << std::endl;
        if (sides_count == 0) std::cout << std::endl;
    }
};

class Triangle : public Figure {
protected:
    unsigned int side_a;
    unsigned int side_b;
    unsigned int side_c;
    unsigned short angle_A;
    unsigned short angle_B;
    unsigned short angle_C;
public:
    Triangle(unsigned int a, unsigned int b, unsigned int c, unsigned short A, unsigned short B, unsigned short C) {
        this->side_a = a;
        this->side_b = b;
        this->side_c = c;
        this->angle_A = A;
        this->angle_B = B;
        this->angle_C = C;

        this->sides_count = 3;
    }
    unsigned int get_side_a() {
        return side_a;
    }
    unsigned int get_side_b() {
        return side_b;
    }
    unsigned int get_side_c() {
        return side_c;
    }
    unsigned short get_angle_A() {
        return angle_A;
    }
    unsigned short get_angle_B() {
        return angle_B;
    }
    unsigned short get_angle_C() {
        return angle_C;
    }
    
    bool check() override {
        if ((sides_count == 3) && (angle_A + angle_B + angle_C == 180)) return true;
        else return false;
    }

    void print() override {
        Figure::print();
        std::cout << "Стороны: а=" << get_side_a() << " b=" << get_side_b() << " c=" << get_side_c() << std::endl;
        std::cout << "Углы: A=" << get_angle_A() << " B=" << get_angle_B() << " C=" << get_angle_C() << std::endl;
        std::cout << std::endl;
    }
};

class RightTriangle : public Triangle {
public:
    RightTriangle(unsigned int a, unsigned int b, unsigned int c, unsigned short A, unsigned short B) : Triangle(a, b, c, A, B, 90) {

    }
    bool check() override {
        if ((Triangle::check()) && (angle_C == 90)) return true;
        else return false;
    }
};

class EquilateralTriangle : public Triangle {
public:
    EquilateralTriangle(unsigned int a) : Triangle(a, a, a, 60, 60, 60) {

    }
    bool check() override {
        if ((Triangle::check()) && ((side_a == side_b) && (side_a == side_c)) && ((angle_A == angle_B) && (angle_A == angle_C)) && (angle_A == 60))
            return true;
        else return false;
    }
};

class IsoscelesTriangle : public Triangle {
public:
    IsoscelesTriangle(unsigned int a, unsigned int b, unsigned short A, unsigned short B) : Triangle(a, b, a, A, B, A) {

    }
    bool check() override {
        if ((Triangle::check()) && (side_a == side_c) && (angle_A == angle_C)) return true;
        else return false;
    }
};

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

    Quadrangle(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned short A, unsigned short B, unsigned short C, unsigned short D) {
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
    unsigned int get_side_a() {
        return side_a;
    }
    unsigned int get_side_b() {
        return side_b;
    }
    unsigned int get_side_c() {
        return side_c;
    }
    unsigned int get_side_d() {
        return side_d;
    }
    unsigned short get_angle_A() {
        return angle_A;
    }
    unsigned short get_angle_B() {
        return angle_B;
    }
    unsigned short get_angle_C() {
        return angle_C;
    }
    unsigned short get_angle_D() {
        return angle_D;
    }
    bool check() override {
        if ((sides_count == 4) && (angle_A + angle_B + angle_C + angle_D == 360)) return true;
        else return false;
    }
    void print() override {
        Figure::print();
        std::cout << "Стороны: а=" << get_side_a() << " b=" << get_side_b() << " c=" << get_side_c() << " d=" << get_side_d() << std::endl;
        std::cout << "Углы: A=" << get_angle_A() << " B=" << get_angle_B() << " C=" << get_angle_C() << " D=" << get_angle_D() << std::endl;
        std::cout << std::endl;
    }
};

class Parallelogram : public Quadrangle {
public:
    Parallelogram(unsigned int a, unsigned int b, unsigned short A, unsigned short B) : Quadrangle(a, b, a, b, A, B, A, B) {

    }
    bool check() override {
        if ((Quadrangle::check()) && ((side_a == side_c) && (side_b == side_d)) && ((angle_A == angle_C) && (angle_B == angle_D))) return true;
        else return false;
    }
};

class RectangleC : public Parallelogram {
public:
    RectangleC(unsigned int a, unsigned int b) : Parallelogram(a, b, 90, 90) {

    }
    bool check() override {
        if ((Parallelogram::check()) && ((angle_A == 90) && (angle_B == 90))) return true;
        else return false;
    }
};

class Rhomb : public Parallelogram {
public:
    Rhomb(unsigned int a, unsigned short A, unsigned short B) : Parallelogram(a, a, A, B) {

    }
    bool check() override {
        if ((Parallelogram::check()) && (side_a == side_b)) return true;
        else return false;
    }
};

class Square : public Rhomb {
public:
    Square(unsigned int a) : Rhomb(a, 90, 90) {

    }
    bool check() override {
        if ((Rhomb::check()) && ((angle_A == 90) && (angle_B == 90))) return true;
        else return false;
    }
};

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Figure figure;
    figure.set_name("Фигура");
    figure.print();

    Triangle triangle(10, 20, 30, 45, 45, 90);
    triangle.set_name("Треугольник");
    triangle.print();

    RightTriangle right_triangle(4, 6, 7, 35, 55);
    right_triangle.set_name("Прямоугольный треугольник");
    right_triangle.print();

    EquilateralTriangle equilateral_triangle(50);
    equilateral_triangle.set_name("Равноcторонний треугольник");
    equilateral_triangle.print();

    IsoscelesTriangle isosceles_triangle(10, 20, 50, 80);
    isosceles_triangle.set_name("Равнобедренный треугольник");
    isosceles_triangle.print();

    Quadrangle quadrangle(10, 20, 30, 40, 25, 30, 90, 75);
    quadrangle.set_name("Четырехугольник");
    quadrangle.print();

    Parallelogram parallelogram(15, 30, 120, 60);
    parallelogram.set_name("Параллелограм");
    parallelogram.print();

    RectangleC rectangle(10, 20);
    rectangle.set_name("Прямоугольник");
    rectangle.print();

    Rhomb rhomb(10, 35, 70);
    rhomb.set_name("Ромб");
    rhomb.print();

    Square square(5);
    square.set_name("Квадрат");
    square.print();
}