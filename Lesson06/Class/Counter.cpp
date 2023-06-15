#include <iostream>
#include "Counter.h"

Counter::Counter() {
    this->count = 1;
}
Counter::Counter(int value) {
    this->count = value;
}
void Counter::inc() {
    this->count++;
}
void Counter::dec() {
    this->count--;
}
void Counter::print() {
    std::cout << this->count << std::endl;
}