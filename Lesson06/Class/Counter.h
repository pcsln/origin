#pragma once

class Counter {
private:
    int count;
public:
    Counter();
    Counter(int value);
    void inc();
    void dec();
    void print();
};
