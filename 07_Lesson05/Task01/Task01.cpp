#include <iostream>
#include <vector>

template<typename T>
auto squaring(T n) {
    return n * n;
}

template<typename T>
auto squaring(std::vector<T> vect) {
    std::vector<T> result;
    for (auto it : vect) {
        result.push_back(it * it);
    }
    return result;
}

int main()
{   
    std::cout << "[IN] " << 2 << " [OUT] " << squaring(2) << std::endl;
    std::cout << "[IN] " << -4 << " [OUT] " << squaring(-4) << std::endl;
    std::cout << "[IN] " << 2.78 << " [OUT] " << squaring(2.78) << std::endl;
    std::cout << "[IN] " << -3.976 << " [OUT] " << squaring(-3.976) << std::endl;
    
    std::vector<int> vect = { 1, 2, 3, 4, 5 };
    std::cout << "[IN] ";
    for (auto it : vect) {
        std::cout << it << " ";
    }
    std::cout << std::endl;
    std::cout << "[OUT] ";
    std::vector<int> result = squaring(vect);
    for (auto it : result) {
        std::cout << it << " ";
    }

    std::cout << std::endl;

    std::vector<double> vect1 = { 1.3, 2.7, 3.6, 4.2, 5.5 };
    std::cout << "[IN] ";
    for (auto it : vect1) {
        std::cout << it << " ";
    }
    std::cout << std::endl;
    std::cout << "[OUT] ";
    std::vector<double> result1 = squaring(vect1);
    for (auto it : result1) {
        std::cout << it << " ";
    }

}
