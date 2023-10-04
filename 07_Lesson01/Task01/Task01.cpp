#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    std::vector<int> v{ 1, 2, 3, 4, 5, 6, 7, 8 };

    auto print = [](const auto& n) { std::cout << n << ' '; };

    std::for_each(v.begin(), v.end(), print);
    std::cout << '\n';

    std::for_each(v.begin(), v.end(), [](auto& n) { if ((n & 1)) { n *= 3; }  });

    std::for_each(v.begin(), v.end(), print);
    std::cout << '\n';

}

