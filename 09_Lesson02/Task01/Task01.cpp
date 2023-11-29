#include <thread>
#include <chrono>
#include <iostream>
#include <atomic>

std::atomic<int> client;

using namespace std::chrono_literals;

void queue(int max_client) {
    while (client != max_client) {
        std::this_thread::sleep_for(1000ms);
        client.fetch_add(1);
        std::cout << " client " << client << std::endl;
    }
}

void operator_() {
    while (client != 0) {
        std::this_thread::sleep_for(2000ms);
        client.fetch_sub(1);
        std::cout << " operator " << client << std::endl;
    }
}

int main()
{
    int max_client = 5;

    client.store(1);

    std::thread t1(queue, max_client);
    std::this_thread::sleep_for(100ms);
    std::thread t2(operator_);
    t1.join();
    t2.join();

}