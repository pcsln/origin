#include <iostream>
#include <Windows.h>

class Figure {
protected:
    int sides_count;
    std::string name;
public:
    Figure(int sides_count) {
        this->sides_count = sides_count;
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
};

class Triangle : public Figure {
public:
    Triangle(int sides_count) : Figure(sides_count) {

    }
};

class Quadrangle : public Figure {
public:
    Quadrangle(int sides_count) : Figure(sides_count) {

    }
};

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Figure figure(0);
    figure.set_name("Фигура");

    Triangle triangle(3);
    triangle.set_name("Треугольник");

    Quadrangle quadrangle(4);
    quadrangle.set_name("Четырехугольник");

    std::cout << "Количество сторон: " << std::endl;

    std::cout << figure.get_name() << ": " << figure.get_sides_count() << std::endl;
    std::cout << triangle.get_name() << ": " << triangle.get_sides_count() << std::endl;
    std::cout << quadrangle.get_name() << ": " << quadrangle.get_sides_count() << std::endl;

}