#include <thread>
#include <queue>
#include <vector>
#include <condition_variable>
#include <atomic>
#include <functional>
#include <mutex>
#include <chrono>
#include <iostream>

template <typename T>
class Safe_queue {
private:
    std::condition_variable cv;
    std::mutex mutex;
    std::queue<T> queue;
public:
    void push(T const function) {
        std::lock_guard<std::mutex> lock(mutex);
        queue.push(function);
        cv.notify_one();
    }

    T pop() {
        std::unique_lock<std::mutex> lock(mutex);
        cv.wait(lock, [this]() { return !queue.empty(); });

        T function = queue.front();
        queue.pop();

        return function;     
    }

    bool empty() {
        std::lock_guard<std::mutex> lock(mutex);
        return queue.empty();
    }
};

class Threads_pool {
private:
    std::atomic_bool flag = true;
    std::mutex print_mutex;
    Safe_queue<std::function<void()>> queue;
    std::vector<std::thread> threads_vector;
    const unsigned short cores = std::thread::hardware_concurrency();

public:
    Threads_pool() {
        for (auto i = 0; i != cores; ++i) {
            threads_vector.push_back(std::thread(&Threads_pool::work, this));
        }
    }
    ~Threads_pool() {
        for (auto& el : threads_vector) {
            el.join();
        }
    }

    void task() {
        auto function = queue.pop();
        print_mutex.lock();
        function();
        print_mutex.unlock();
    }
    
    void work() {

        while (flag) {
            if (!queue.empty()) {
                task();
            }
            else std::this_thread::yield();
        }

        while (!queue.empty()) {
            task();
        }
    }

    void submit(std::function<void()> function) {
        queue.push(function);
    }

    void set_flag(bool value) {
        flag.store(value);
    }
};

void function_one() {
    std::cout << std::this_thread::get_id() << " " << __FUNCTION__ << std::endl;
}

void function_two() {
    std::cout << std::this_thread::get_id() << " " << __FUNCTION__ << std::endl;
}

int main()
{
    Threads_pool threads_pool;

    for (auto i = 0; i != 5; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds{ 1000 });
        threads_pool.submit(function_one);
        threads_pool.submit(function_two);
    }

    threads_pool.set_flag(false);
}
