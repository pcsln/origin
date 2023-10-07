#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

int main()
{
    std::string string = "A young dog, a reddish mongrel, between a dachshund and a yard - dog, very like a fox in face, was running up and down the pavement looking uneasily from side to side. From time to time she stopped and, whining and lifting first one chilled paw and then another, tried to make up her mind how it could have happened that she was lost.";
    std::cout << "[IN]: " << string << std::endl;

    std::map<char, int> freq;

    for (int i = 0; i < string.length(); ++i) {
        freq[string[i]]++;
    }

    std::vector<std::pair<char, int>> chars(freq.begin(), freq.end());
    sort(chars.begin(), chars.end(), [](const auto& l, const auto& r) {return r.second < l.second; });

    std::cout << "[OUT]:" << std::endl;
    for (auto it : chars) {
        std::cout << it.first << " " << it.second << std::endl;
    }

}
