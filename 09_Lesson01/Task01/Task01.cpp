#include <thread>
#include <chrono>
#include <iostream>

int client = 1;

using namespace std::chrono_literals;

void queue(int max_client) {
    while (client != max_client) {
        std::this_thread::sleep_for(1000ms);
        client++;
        std::cout << " client " << client << std::endl;
    }
}

void operator_() {
    while (client != 0) {
        std::this_thread::sleep_for(2000ms);
        client--;
        std::cout << " operator " << client << std::endl;
    }
}

int main()
{
    int max_client = 10;
 
    std::thread t1(queue, max_client);
    std::this_thread::sleep_for(10ms);
    std::thread t2(operator_);
    t1.join();
    t2.join();
    
}


