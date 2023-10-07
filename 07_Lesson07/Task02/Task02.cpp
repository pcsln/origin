﻿#include <vector>
#include <set>
#include <list>
#include <iostream>

template<typename T>
void print_container(const T conteiner) {
    for (auto it : conteiner) {
        std::cout << it << " ";
    }
    std::cout << std::endl;
}

int main()
{
    std::set<std::string> test_set = { "one", "two", "three", "four" };
    print_container(test_set);

    std::list<std::string> test_list = { "one", "two", "three", "four" };
    print_container(test_list);

    std::vector<std::string> test_vector = { "one", "two", "three", "four" };
    print_container(test_vector);
}


