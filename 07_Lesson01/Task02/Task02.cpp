#include <iostream>
#include <variant>
#include <vector>


std::variant<int, std::string, std::vector<int>> get_variant() {
	std::srand(std::time(nullptr));
	int random_variable = std::rand() % 3;

	std::variant<int, std::string, std::vector<int>> result;
	switch (random_variable)
	{
	case 0:
		result = 5;
		break;
	case 1:
		result = "string";
		break;
	case 2:
		result = std::vector<int>{ 1, 2, 3, 4, 5 };
		break;
	default:
		break;
	}
	return result;
}

int main()
{
	auto value = get_variant();
	if (std::holds_alternative<int>(value)) {
		std::cout << std::get<int>(value) * 2;
	} 
	else if (std::holds_alternative<std::string>(value)) {
		std::cout << std::get<std::string>(value);
	}
	else {
		auto v = std::get<std::vector<int>>(value);
		for (auto i : v) {
			std::cout << i << " ";
		}
	}
}
