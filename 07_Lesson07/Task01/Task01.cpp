#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    std::vector<int> vector = { 1, 1, 2, 5, 6, 1, 2, 4 };
    std::cout << "[IN]: ";
    for (auto it : vector) {
        std::cout << it << " ";
    }
    std::cout << std::endl;

    std::sort(vector.begin(), vector.end());

    auto it = std::unique(vector.begin(), vector.end());
    vector.erase(it, vector.end());

    std::cout << "[OUT]: ";
    for (auto it : vector) {
        std::cout << it << " ";
    }

}

