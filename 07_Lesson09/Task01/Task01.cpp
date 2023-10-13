#include <vector>
#include <iostream>

template <typename T>
void move_vectors(T& lhs, T& rhs) {
    rhs = std::move(lhs);
}


int main()
{
    std::vector <std::string> one = { "test_string1", "test_string2" };
    std::vector <std::string> two;
    move_vectors(one, two);

    std::cout << "Vector two" << std::endl;
    for (auto it : two) {
        std::cout << it << " ";
    }
}
