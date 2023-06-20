#pragma once
#include <iostream>

class Figure {
protected:
    int sides_count;
    std::string name;
public:
    Figure();
    int get_sides_count();
    void set_name(std::string name);
    std::string get_name();
    virtual void print() {
        std::cout << get_name() << std::endl;
        std::cout << "Количество сторон: " << get_sides_count() << std::endl;
        if (sides_count == 0) std::cout << std::endl;
    }
};