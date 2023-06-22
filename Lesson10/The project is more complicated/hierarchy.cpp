#include <iostream>
#include <Windows.h>
#include "Figure.h"
#include "Triangle.h"
#include "RightTriangle.h"
#include "EquilateralTriangle.h"
#include "IsoscelesTriangle.h"
#include "Quadrangle.h"
#include "Parallelogram.h"
#include "RectangleC.h"
#include "Rhomb.h"
#include "Square.h"

void print_info(Figure* figure) {
    figure->print();
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Figure figure;
    figure.set_name("Фигура");

    Triangle triangle(10, 20, 30, 45, 45, 90);
    triangle.set_name("Треугольник");

    RightTriangle right_triangle(4, 6, 7, 35, 55);
    right_triangle.set_name("Прямоугольный треугольник");

    EquilateralTriangle equilateral_triangle(50);
    equilateral_triangle.set_name("Равноcторонний треугольник");

    IsoscelesTriangle isosceles_triangle(10, 20, 50, 80);
    isosceles_triangle.set_name("Равнобедренный треугольник");

    Quadrangle quadrangle(10, 20, 30, 40, 25, 30, 90, 75);
    quadrangle.set_name("Четырехугольник");

    Parallelogram parallelogram(15, 30, 120, 60);
    parallelogram.set_name("Параллелограм");

    RectangleC rectangle(10, 20);
    rectangle.set_name("Прямоугольник");

    Rhomb rhomb(10, 35, 70);
    rhomb.set_name("Ромб");

    Square square(5);
    square.set_name("Квадрат");

    print_info(&figure);
    print_info(&triangle);
    print_info(&right_triangle);
    print_info(&equilateral_triangle);
    print_info(&isosceles_triangle);
    print_info(&quadrangle);
    print_info(&parallelogram);
    print_info(&rectangle);
    print_info(&rhomb);
    print_info(&square);
}