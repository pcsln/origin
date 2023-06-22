#include "Figure.h"

Figure::Figure() {
    this->sides_count = 0;
}
int Figure::get_sides_count() {
    return sides_count;
}
void Figure::set_name(std::string name) {
    this->name = name;
}
std::string Figure::get_name() {
    return name;
}
