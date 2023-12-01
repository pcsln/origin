#include <mutex>
#include <thread>
#include <iostream>

class Data {
public:
	std::mutex mutex;
	int integer;
	double numeric;
	Data(int i, double d) {
		integer = i;
		numeric = d;
	}
	void print() {
		std::cout << integer << " " << numeric << std::endl;
	}
};

void swap_data_lock(Data& data_1, Data& data_2) {

	std::lock(data_1.mutex, data_2.mutex);

	auto temp_1 = data_1.integer;
	auto temp_2 = data_1.numeric;
	data_1.integer = data_2.integer;
	data_1.numeric = data_2.numeric;
	data_2.integer = temp_1;
	data_2.numeric = temp_2;
	data_1.mutex.unlock();
	data_2.mutex.unlock();
}

void swap_data_scoped_lock(Data& data_1, Data& data_2) {

	std::scoped_lock lock{ data_1.mutex, data_2.mutex };

	auto temp_1 = data_1.integer;
	auto temp_2 = data_1.numeric;
	data_1.integer = data_2.integer;
	data_1.numeric = data_2.numeric;
	data_2.integer = temp_1;
	data_2.numeric = temp_2;
}

void swap_data_unique_lock(Data& data_1, Data& data_2) {

	std::unique_lock<std::mutex> lock1(data_1.mutex, std::defer_lock);
	std::unique_lock<std::mutex> lock2(data_2.mutex, std::defer_lock);

	std::lock(lock1, lock2);

	auto temp_1 = data_1.integer;
	auto temp_2 = data_1.numeric;
	data_1.integer = data_2.integer;
	data_1.numeric = data_2.numeric;
	data_2.integer = temp_1;
	data_2.numeric = temp_2;
}



int main()
{
	Data data_1(11, 11.11), data_2(22, 22.22);
	
	data_1.print();
	data_2.print();

	swap_data_lock(data_1, data_2);

	std::cout << std::endl;
	data_1.print();
	data_2.print();

	swap_data_scoped_lock(data_1, data_2);

	std::cout << std::endl;
	data_1.print();
	data_2.print();

	swap_data_unique_lock(data_1, data_2);

	std::cout << std::endl;
	data_1.print();
	data_2.print();




}

