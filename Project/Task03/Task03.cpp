#include <fstream> 
#include <iostream>
#include <map>
#include <string>
#include <Windows.h>


class ini_parser {
private:
    std::fstream file;
    std::string filename;
public:
    std::map<std::string, std::string> ini_data;
    ini_parser(std::string filename) {
        this->filename = filename;

    }
    ~ini_parser() {}

    void fill_ini_data() {
        std::string current_section = "";
        std::string string;
       
            std::ifstream file(filename);
            if (!file.is_open()) {
                std::cout << "INI файл не найден или поврежден.";
                exit(EXIT_FAILURE);
            }

		while (getline(file, string)) {
			string.erase(std::remove_if(string.begin(), string.end(), [](char c) { return c == ' '; }), string.end());
			std::string::size_type n = string.find(';');
			if (n != std::string::npos) {
				string.erase(n, string.length() - n);
			}
            
            if (string != "") {
                if (string[0] == '[') {
                    current_section = string.substr(1, string.length() - 2);
                }
                else {
                    int position = 0;
                    for (int i = 0; i < string.length(); ++i) {
                        if (string[i] == '=') {
                            position = i;
                            break;
                        }
                    }
                    ini_data[current_section + "." + string.substr(0, position)] = string.substr(position + 1, string.length() - 1);
                }
            }
		}

        file.close();

        for (auto it : ini_data) {
            std::cout << it.first << " " << it.second << std::endl;
        }
    


    }

    bool check_value(std::string key) {
        
        if (ini_data[key] == "") {
            std::cout << "Значение переменной в файле " << filename << " не определено.";
            exit(EXIT_FAILURE);
        }
        else {
            return true;
        }
    }

    template <typename T>
    T get_value(std::string key) {
        fill_ini_data();
        if (check_value(key)) return ini_data[key];
    }
    template <>
    int get_value(std::string key) {
        fill_ini_data();
        if (check_value(key)) return std::stoi(ini_data[key]);
    }
    template <>
    double get_value(std::string key) {
        fill_ini_data();
        if (check_value(key)) return std::atof(ini_data[key].c_str());
    }

};

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    
    ini_parser parser("ini.txt");
    auto value = parser.get_value<double>("Section1.var1");
    
    std::cout << std::endl << "Значение запрошенного параметра равно " << value << std::endl;
}
