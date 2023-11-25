#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <execution>
#include <chrono>
#include <thread>
#include <iomanip>
#include <mutex>

std::once_flag flag;

void print_hardware_concurrency()
{
    std::cout << "Hardware concurrency: " << std::thread::hardware_concurrency() << std::endl << std::endl;
}

std::vector<int> addition(std::vector<int> vector_1, std::vector<int> vector_2) {
    std::call_once(flag, print_hardware_concurrency);
    std::vector<int> result;
    for (auto i = 0; i != vector_1.size(); ++i) {
        result.push_back(vector_1[i] + vector_2[i]);
    }
    return result;
}


int main()
{   
    std::vector<std::vector<double>> result_time(4);
    auto result_time_i = 0;
    
    for (auto vector_size = 1000; vector_size != 10000000; vector_size *= 10) {

        std::vector<int> vector_1(vector_size);
        std::vector<int> vector_2(vector_size);
        std::vector<int> vector_add(vector_size);
        std::mt19937 gen;
        std::uniform_int_distribution<int> dis(0, vector_size);
        auto rand_num([=]() mutable { return dis(gen); });

        generate(vector_1.begin(), vector_1.end(), rand_num);
        generate(vector_2.begin(), vector_2.end(), rand_num);



        for (auto j = 1; j != 32; j = j * 2) {
            auto start = std::chrono::steady_clock::now();

            std::vector<std::thread> TV;
            for (size_t i = 0; i != j; i++)
            {
                TV.push_back(std::thread(addition, vector_1, vector_2));
            }
            for (auto& t : TV)
            {
                t.join();
            }

            auto end = std::chrono::steady_clock::now();
            std::chrono::duration<double> elapsed_seconds = end - start;
            result_time[result_time_i].push_back(elapsed_seconds.count());
            
        }
        ++result_time_i;
    }

    std::cout << std::setw(28) << "1000";
    std::cout << std::setw(17) << "10 000";
    std::cout << std::setw(15) << "100 000";
    std::cout << std::setw(15) << "1 000 000";
    std::cout << std::endl;

    auto count_threads = 1;
    for (size_t i = 0; i < result_time[0].size(); ++i) {
        count_threads == 1 ? std::cout <<  count_threads << " thread \t" 
                           : std::cout <<  count_threads << " threads \t";
        count_threads *= 2;
        for (size_t j = 0; j < result_time.size(); ++j) {
            std::cout << std::setw(15) << result_time[j][i];
        }
        std::cout << "\n";
    }
}
