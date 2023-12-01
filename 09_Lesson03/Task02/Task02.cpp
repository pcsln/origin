#include <vector>
#include <future>
#include <iostream>

template<typename Iterator, typename T>
void parallel_for_each(Iterator first, Iterator last, T function)
{
	unsigned long const length = std::distance(first, last);
	unsigned long const max_chunk_size = 5;
	if (length <= max_chunk_size)
	{
		for (auto iterator = first; iterator != last; ++iterator) {
			*iterator = function(*iterator);
		}
		return;
	}
	else
	{
		Iterator mid_point = first;
		std::advance(mid_point, length / 2);
		auto first_half_result = std::async(parallel_for_each<Iterator, T>, first, mid_point, function);
		auto second_half_result = std::async(parallel_for_each<Iterator, T>, mid_point, last, function);
		
	}
}


int main()
{
	std::vector<int> vector(30, 2);

	for (auto& it : vector) {
		std::cout << it << " ";
	}

	std::cout << std::endl;

	parallel_for_each(vector.begin(), vector.end(), [](auto x) { return x * x; });

	for (auto& it : vector) {
		std::cout << it << " ";
	}
}

