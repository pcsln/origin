#include <iostream>

class smart_array {
private:
    int max_index;
    int size;
    int* a;
public:
    smart_array(int count_elements) {
        a = new int[count_elements]();
        size = count_elements;
        max_index = -1;
    }
    ~smart_array() {
        delete[] a;
    }
    void add_element(int element) {
        if (max_index == size - 1) {
            return;
        }
        else {
            a[max_index + 1] = element;
            max_index++;
        }
    }
    int get_element(int i) {
        if ((i < 0) || (i > size - 1)) {
            return a[max_index];
        }
        else {
            return a[i];
        }  
    }
};

int main()
{
    try {
        smart_array arr(5);
        arr.add_element(1);
        arr.add_element(4);
        arr.add_element(155);
        arr.add_element(14);
        arr.add_element(15);
        std::cout << arr.get_element(2) << std::endl;
    }
    catch (const std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }
}
