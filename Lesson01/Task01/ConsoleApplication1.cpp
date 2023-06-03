#include <iostream>
#include <fstream>

void array_shift(int* array, int size) {
    
    int temp = array[size - 1];

    for (int i = size - 1; i > 0; --i) {
        array[i] = array[i - 1];
    }

    array[0] = temp;
}

int main()
{
    setlocale(LC_ALL, "Russian");

    int N = 0;
    int M = 0;

    std::ifstream file("in.txt");

    if (!file.is_open()) {
        std::cout << "Не получилось открыть файл in.txt\n";
        return 1;
    }

    file >> N;
    int* array_N = new int[N];
    for (int i = 0; i < N; ++i) {
        file >> array_N[i];
    }

    file >> M;
    int* array_M = new int[M];
    for (int i = 0; i < M; ++i) {
        file >> array_M[i];
    }

    file.close();

    array_shift(array_N, N);
    array_shift(array_M, M);

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

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
