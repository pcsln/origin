#include <iostream>
#include <string>


template<typename T>
class matrix {
private:
    int rows;
    int cols;
    T** table;
public:
    class wraptable {
    private:
        T* table = nullptr;
        int cols = 0;
    public:
        wraptable(T* table, int cols) {
            this->table = table;
            this->cols = cols;
        }
        const T& operator[](const int i) const {
            if ((i < 0) || (i > cols)) {
                throw std::runtime_error("Out of Bounds");
            }
            return table[i];

        }
        T& operator[](const int i) {
            if ((i < 0) || (i > cols)) {
                throw std::runtime_error("Out of Bounds");
            }
            return table[i];
        }      
    };

    matrix(int rows, int cols) {
        this->rows = rows;
        this->cols = cols;
        
        table = new T*[rows];
        for (int i = 0; i < rows; ++i) {
            table[i] = new T[cols]();
        }

    }
    matrix(const matrix& other) {
        this->rows = other.rows;
        this->cols = other.cols;

        table = new T * [rows];
        for (int i = 0; i < rows; ++i) {
            table[i] = new T[cols]();
        }

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                table[i][j] = other.table[i][j];
            }
        }

    }
    ~matrix() {
        for (int i = 0; i < rows; ++i) {
            delete[] table[i];
        }
        delete[] table;
    }
    matrix& operator=(const matrix& other) {
        if (&other == this) {
            return *this;
        }

        for (int i = 0; i < rows; ++i) {
            delete[] table[i];
        }
        delete[] table;
        
        this->rows = other.rows;
        this->cols = other.cols;

        table = new T * [rows];
        for (int i = 0; i < rows; ++i) {
            table[i] = new T[cols]();
        }

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                table[i][j] = other.table[i][j];
            }
        }
        return *this;
    }
    const wraptable operator[](const int i) const {
        if ((i < 0) || (i > rows)) {
            throw std::runtime_error("Out of Bounds");
       }
        return wraptable(table[i], cols);
     
    }
    wraptable operator[](const int i) {
           if ((i < 0) || (i > rows)) {
               throw std::runtime_error("Out of Bounds");
           }
           return wraptable(table[i], cols);
        
    }
    const std::string size() {
        return std::to_string(rows) + "x" + std::to_string(cols);
    }
    int get_rows() {
        return rows;
    }
    int get_cols() {
        return cols;
    }
};


int main()
{
    auto test = matrix<int>(12, 8);
    
    int k = 1;
    for (auto i = 0; i < test.get_rows(); ++i) {
        for (auto j = 0; j < test.get_cols(); ++j) {
            test[i][j] = k++;
        }
    }

    for (auto i = 0; i < test.get_rows(); ++i) {
        for (auto j = 0; j < test.get_cols(); ++j) {
            std::cout << test[i][j] << "\t";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;

    std::cout << "Matrix size: " << test.size() << std::endl;
}
