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

    smart_array(const smart_array&) = delete;
    smart_array& operator=(const smart_array&) = delete;

    void add_element(int element) {
        if (max_index == size - 1) {
            std::cout << "Attempt to add an element to a filled array." << std::endl;
            return;
        }
        else {
            a[max_index + 1] = element;
            max_index++;
        }
    }
    int get_element(int i) {
        if ((i < 0) || (i > max_index)) {
            std::cout << "An attempt to access a non-existent element." << std::endl;
            return 0;
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
        arr.add_element(16);
        std::cout << arr.get_element(3) << std::endl;

        //smart_array arr2 = arr;
    }
    catch (const std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }
}
