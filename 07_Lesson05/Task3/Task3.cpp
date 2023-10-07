#include <iostream>
#include <vector>

class functor {
private:
    int sum = 0;
    int count = 0;
public:
    void operator() (int i) {
        if (i % 3 == 0) {
            sum += i;
            count++;
        }
    }
    int get_sum() {
        return sum;
    }
    int get_count() {
        return count;
    }
};

int main()
{
    functor functor;
    std::vector<int> vect = { 4, 1, 3, 6, 25, 54 };

    std::cout << "[IN] : ";
    for (auto it : vect) {
        std::cout << it << " ";
        functor(it);
    }
    std::cout << std::endl;
    std::cout << "[OUT]:  get_sum() = " << functor.get_sum() << std::endl;
    std::cout << "[OUT]:  get_count() = " << functor.get_count() << std::endl;

}
