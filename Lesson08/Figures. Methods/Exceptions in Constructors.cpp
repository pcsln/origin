#include <iostream>
#include <Windows.h>
#include "Figure.h"
#include "Triangle.h"
#include "RightTriangle.h"
#include "IncorrectFigure.h"
#include "EquilateralTriangle.h"
#include "IsoscelesTriangle.h"
#include "Quadrangle.h"
#include "Parallelogra.h"
#include "RectangleC.h"
#include "Rhomb.h"
#include "Square.h"

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Figure figure;
    figure.set_name("Фигура");
    figure.print();

    
    try {
        Triangle triangle(10, 20, 30, 45, 46, 90);
        triangle.set_name("Треугольник");
        triangle.print();
    }
    catch (IncorrectFigure& ex) {
        std::cout << ex.what() << std::endl;
    }
    
    try {
        Triangle triangle(10, 20, 30, 45, 45, 90);
        triangle.set_name("Треугольник");
        triangle.print();
    }
    catch (IncorrectFigure& ex) {
        std::cout << ex.what() << std::endl;
    }

    try {
        RightTriangle right_triangle(4, 6, 7, 55, 55);
        right_triangle.set_name("Прямоугольный треугольник");
        right_triangle.print();
    }
    catch (IncorrectFigure& ex) {
        std::cout << ex.what() << std::endl;
    }

    try {
        RightTriangle right_triangle(4, 6, 7, 35, 55);
        right_triangle.set_name("Прямоугольный треугольник");
        right_triangle.print();
    }
    catch (IncorrectFigure& ex) {
        std::cout << ex.what() << std::endl;
    }

    try
    {
        EquilateralTriangle equilateral_triangle(50);
        equilateral_triangle.set_name("Равноcторонний треугольник");
        equilateral_triangle.print();
    }
    catch (IncorrectFigure& ex)
    {
        std::cout << ex.what() << std::endl;
    }

    try
    {
        IsoscelesTriangle isosceles_triangle(10, 20, 80, 80);
        isosceles_triangle.set_name("Равнобедренный треугольник");
        isosceles_triangle.print();
    }
    catch (IncorrectFigure& ex)
    {
        std::cout << ex.what() << std::endl;
    }

    try
    {
        IsoscelesTriangle isosceles_triangle(10, 20, 50, 80);
        isosceles_triangle.set_name("Равнобедренный треугольник");
        isosceles_triangle.print();
    }
    catch (IncorrectFigure& ex)
    {
        std::cout << ex.what() << std::endl;
    }

    try
    {
        Quadrangle quadrangle(10, 20, 30, 40, 25, 30, 90, 75);
        quadrangle.set_name("Четырехугольник");
        quadrangle.print();
    }
    catch (IncorrectFigure& ex)
    {
        std::cout << ex.what() << std::endl;
    }

    try
    {
        Quadrangle quadrangle(10, 20, 30, 40, 145, 35, 95, 85);
        quadrangle.set_name("Четырехугольник");
        quadrangle.print();
    }
    catch (IncorrectFigure& ex)
    {
        std::cout << ex.what() << std::endl;
    }

    try
    {
        Parallelogram parallelogram(15, 30, 120, 60);
        parallelogram.set_name("Параллелограм");
        parallelogram.print();
    }
    catch (IncorrectFigure& ex)
    {
        std::cout << ex.what() << std::endl;
    }

    try
    {
        RectangleC rectangle(10, 20);
        rectangle.set_name("Прямоугольник");
        rectangle.print();
    }
    catch (IncorrectFigure& ex)
    {
        std::cout << ex.what() << std::endl;
    }

    try
    {
        Rhomb rhomb(10, 35, 70);
        rhomb.set_name("Ромб");
        rhomb.print();
    }
    catch (IncorrectFigure& ex)
    {
        std::cout << ex.what() << std::endl;
    }

    try
    {
        Rhomb rhomb(10, 100, 80);
        rhomb.set_name("Ромб");
        rhomb.print();
    }
    catch (IncorrectFigure& ex)
    {
        std::cout << ex.what() << std::endl;
    }

    try
    {
        Square square(5);
        square.set_name("Квадрат");
        square.print();
    }
    catch (IncorrectFigure& ex)
    {
        std::cout << ex.what() << std::endl;
    }
}