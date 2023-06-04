#include <iostream>
#include <fstream>

int main()
{
    setlocale(LC_ALL, "Russian");

    int N = 0;
    int M = 0;

    std::ifstream file_in("in.txt");

    if (!file_in.is_open()) {
        std::cout << "Не получилось открыть файл in.txt\n";
        return 1;
    }

    file_in >> N;
    int* array_N = new int[N];
    for (int i = 0; i < N; ++i) {
        file_in >> array_N[i];
    }

    file_in >> M;
    int* array_M = new int[M];
    for (int i = 0; i < M; ++i) {
        file_in >> array_M[i];
    }

    file_in.close();

    int temp = array_N[0];
    for (int i = 0; i < N - 1; ++i) {
        array_N[i] = array_N[i + 1];
    }
    array_N[N - 1] = temp;

    temp = array_M[M - 1];
    for (int i = M - 1; i > 0; --i) {
        array_M[i] = array_M[i - 1];
    }
    array_M[0] = temp;

    std::ofstream file_out("out.txt");

    if (!file_out.is_open()) {
        std::cout << "Не получилось открыть файл out.txt\n";
        return 1;
    }

    file_out << M << "\n";
    for (int i = 0; i <= M - 1; ++i) {
        file_out << array_M[i] << " ";
    }
    file_out << "\n";

    file_out << N << "\n";
    for (int i = 0; i <= N - 1; ++i) {
        file_out << array_N[i] << " ";
    }
    file_out << "\n";

    file_out.close();
    delete[] array_N;
    delete[] array_M;
}