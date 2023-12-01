#include <vector>
#include <iostream>
#include <future>
#include <ctime>

void print(std::vector<int>& array) {
    for (auto& it : array) {
        std::cout << it << " ";
    }
    std::cout << std::endl;
}

void find_minimum_index(const std::vector<int>& array, int begin, std::promise<int> promise) {
    auto result = begin;
    for (size_t i = begin + 1; i != array.size(); ++i) {
        if (array[i] < array[result]) result = i;
    }
    promise.set_value(result);
}

void selection_sort(std::vector<int>& array, int begin) {

    if (begin == array.size()) return;

    std::promise<int> f_promise;
    std::future<int> f_future = f_promise.get_future();
    auto a = std::async(std::launch::async, find_minimum_index, array, begin, move(f_promise));
    auto min = f_future.get();

    auto temp = array[begin];
    array[begin] = array[min];
    array[min] = temp;

    selection_sort(array, begin + 1);
}

int main()
{
    std::srand(time(0));

    int N = 35;
    std::vector<int> array(N);

    for (size_t i = 0; i != N; ++i) {
        array[i] = std::rand() % 100;
    }

    print(array);

    std::cout << std::endl;

    selection_sort(array, 0);

    print(array);
}

