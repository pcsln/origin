#include <thread>
#include <iostream>
#include <mutex>
#include <Windows.h>

using namespace std::chrono_literals;

std::mutex mutex;

class consol_parameter
{
public:
    static void SetColor(int text, int background)
    {
        SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
    }
    static void SetPosition(int x, int y)
    {
        COORD point;
        point.X = x;
        point.Y = y;
        SetConsoleCursorPosition(hStdOut, point);
    }
private:
    static HANDLE hStdOut;
};
HANDLE consol_parameter::hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

std::once_flag flag;

void print_header(int calculation_length)
{
    std::unique_lock<std::mutex> lock(mutex);
    consol_parameter::SetPosition(0, 0);
    std::cout << '#';
    consol_parameter::SetPosition(3, 0);
    std::cout << "id";
    consol_parameter::SetPosition(10, 0);
    std::cout << "Progress bar";
    consol_parameter::SetPosition(calculation_length + 13, 0);
    std::cout << "Time";
    lock.unlock();
}

void imitation(int i, int calculation_length) {

    std::call_once(flag, print_header, calculation_length);

    std::unique_lock<std::mutex> lock_(mutex);
    consol_parameter::SetPosition(0, i + 1);
    std::cout << i << " " << std::this_thread::get_id();
    lock_.unlock();

    int k = 0;

    auto start = std::chrono::steady_clock::now();

    while (k < calculation_length) {

        std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::milliseconds(i * (185 + std::rand() % 100)));

        std::unique_lock<std::mutex> lock(mutex);
        consol_parameter::SetPosition(k + 10, i + 1);
        std::cout << char(219);
        lock.unlock();

        ++k;
    }

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;

    std::unique_lock<std::mutex> lock(mutex);
    consol_parameter::SetPosition(k + 13, i + 1);
    std::cout << elapsed_seconds.count();
    lock.unlock(); 
}

int main()
{
    int threads = 10;
    int calculation_length = 12;


    std::thread* thread = new std::thread[threads];

    for (size_t i = 0; i != threads; ++i)
    {    
        thread[i] = std::thread(imitation, i, calculation_length);
    }
    for (size_t i = 0; i != threads; ++i)
    {
        thread[i].join();
    }

    delete[] thread;

    consol_parameter::SetPosition(0, threads + 1);
}
