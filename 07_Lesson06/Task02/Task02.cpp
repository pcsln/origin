#include <iostream>
#include <set>

int main()
{
    unsigned int count = 0;

    std::cout << "[IN]:" << std::endl;

    std::cin >> count;

    std::set<int, std::greater<int>> num;

    for (auto i = 1; i <= count; ++i) {
        int n;
        std::cin >> n;
        num.insert(n);
    }

    std::cout << "[OUT]" << std::endl << std::endl;

    for (auto it : num) {
        std::cout << it << std::endl;
    }
}
