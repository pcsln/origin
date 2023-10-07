#include <iostream>
#include <string>


template<typename T>
class matrix {
private:
    int rows;
    int cols;
    T** table;
public:
    matrix(int rows, int cols) {
        this->rows = rows;
        this->cols = cols;
        
        table = new T*[rows];
        for (int i = 0; i < rows; ++i) {
            table[i] = new T[cols]();
        }

    }
    ~matrix() {
        for (int i = 0; i < rows; ++i) {
            delete[] table[i];
        }
        delete[] table;
    }
    const T* operator[](const int i) const {
        return table[i];
    }
    T* operator[](const int i) {
        return table[i];
    }
    const std::string size() {
        return std::to_string(rows) + "x" + std::to_string(cols);
    }
};


int main()
{
    auto test = matrix<int>(20, 12);
    test[1][1] = 4;
    test[4][10] = -3;
    test[2][8] = 12;
    std::cout << "[1][1] = " << test[1][1] << std::endl;
    std::cout << "[4][10] = " << test[4][10] << std::endl;
    std::cout << "[2][8] = " << test[2][8] << std::endl;
    std::cout << std::endl;

    std::cout << "Matrix size: " << test.size();
}
