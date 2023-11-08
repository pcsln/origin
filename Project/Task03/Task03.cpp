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

    std::map<std::string, std::string> fill_ini_data() {
        std::map<std::string, std::string> ini_data;
        std::string current_section = "";
        std::string string;

        
            std::ifstream file(filename);
            if (!file.is_open()) {
                throw std::runtime_error("Файл не найден или поврежден.");
            }
        
            while (getline(file, string)) {
                std::string::size_type n = string.find(';');
                if (n != std::string::npos) {
                    string.erase(n);
                }

                if ((string != "") && (string[0] != ' ')) {
                    std::string key = "";
                    std::string value = "";

                    if (string.starts_with("[Section")) {
                        current_section = string.substr(1, string.length() - 2);
                    }
                    else {
                        std::string::size_type position = string.find('=');
                        key = string.substr(0, position);
                        key.erase(std::remove_if(key.begin(), key.end(), [](char c) { return c == ' '; }), key.end());
                        value = string.substr(position + 1, string.length() - 1);

                        ini_data[current_section + "." + key] = value;
                    }
                }
            }

            file.close();

            for (auto it : ini_data) {
                std::cout << it.first << " " << it.second << std::endl;
            }
        
            return ini_data;
    }

    ini_parser(std::string filename) {
        this->filename = filename;
        ini_data = fill_ini_data();
    }
    ~ini_parser() {}

    bool check_value(std::string key) {
        
            if (ini_data[key] == "") {
                throw std::runtime_error("Значение переменной в файле не определено.");
            }
            else {
                return true;
            }
    }

    template <typename T>
    T get_value(std::string key) {
        if (check_value(key)) return ini_data[key];
    }
    template <>
    int get_value(std::string key) {
        if (check_value(key)) return std::stoi(ini_data[key]);
    }
    template <>
    double get_value(std::string key) {
            if (check_value(key)) return std::atof(ini_data[key].c_str()); 

    }

};

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    
    ini_parser parser("ini.txt");
    
    auto value_double = parser.get_value<double>("Section1.var1");
    auto value_int = parser.get_value<int>("Section2.var1");
    
    std::cout << std::endl << parser.get_value<std::string>("Section2.var2") << value_int + value_double << std::endl;
}
