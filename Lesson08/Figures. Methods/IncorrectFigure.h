#pragma once
#include <iostream>

class IncorrectFigure : public std::domain_error {
public:
    using domain_error::domain_error;
};