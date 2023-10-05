#include <iostream>

class smart_array {
private:
    int max_index;
    int size;
    int* a;
    void create(int count_elements) {
        a = new int[count_elements]();
        size = count_elements;
        max_index = -1;
    }
public:
    smart_array(int count_elements) {
        create(count_elements);
    }
    smart_array(smart_array& other) {
        create(other.get_size());

        for (int i = 0; i < other.get_size(); ++i) {
            add_element(other.get_element(i));
        }
    }
    ~smart_array() {
        std::cout << "delete" << std::endl;
        delete[] a;
    }

    smart_array& operator=(smart_array& other) {
        delete[] a;

        create(other.get_size());

        for (int i = 0; i < other.get_size(); ++i) {
            add_element(other.get_element(i));
        }
        
        return *this;
    }

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
    int get_size() {
        return size;
    }
    void print_array(std::string string) {
        std::cout << string << std::endl;
        for (int i = 0; i < size; ++i) {
            std::cout << get_element(i) << " ";
        }
        std::cout << std::endl;
    }
};

int main()
{
    smart_array arr(5);
    arr.add_element(1);
    arr.add_element(4);
    arr.add_element(155);
    arr.add_element(9);
    arr.add_element(6);

    smart_array new_array(2);
    new_array.add_element(44);
    new_array.add_element(34);

    arr.print_array("First array: ");
    new_array.print_array("Second array: ");

    smart_array third_array(arr);
    arr = new_array;

    std::cout << "After copy +++++++++++++++++++" << std::endl;;
    
    arr.print_array("First array: ");
    new_array.print_array("Second array: ");
    third_array.print_array("Third array: ");

}