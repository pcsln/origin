#include <iostream>
#include <functional>
#include <cmath>

int main()
{
	std::vector<int> angles = {0, 30, 45, 90 };
	
	std::function<void(const int& n)> cosinus = [](const int& n) { std::cout << " cos " << cos(n * 3.14 / 180); };
	std::function<void(const int& n)> sinus =  [](const int& n) { std::cout << " sin " << sin(n * 3.14 / 180); };

	std::vector<std::function<void(const int &n)>> functions;

	functions.push_back(cosinus);
	functions.push_back(sinus);


	for (const auto& angle : angles) {
		std::cout << angle << ": ";
		for (const auto& function : functions)
			function(angle);
		std::cout << std::endl;
	}

}
