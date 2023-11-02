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
    bool is_value_found = true;
    bool is_file_open = true;

    void fill_ini_data() {
        std::string current_section = "";
        std::string string;

        try {
            std::ifstream file(filename);
            if (!file.is_open()) {
                throw std::ios_base::failure("Файл не найден или поврежден.");
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
        catch (const std::exception& e) {
            std::cerr << "Ошибка: " << e.what() << std::endl;
            file.close();
            is_file_open = false;
        }

        
    }

    ini_parser(std::string filename) {
        this->filename = filename;

        fill_ini_data();

    }
    ~ini_parser() {}

    bool check_value(std::string key) {
        
        try {
            if (ini_data[key] == "") {
                throw std::invalid_argument("Значение переменной в файле не определено.");
            }
            else {
                return true;
            }
        }
        catch (const std::exception& e) {
            std::cerr << "Ошибка: " << e.what() << std::endl;
            is_value_found = false;
            return false;
        }
     
    }

    template <typename T>
    T get_value(std::string key) {
        //fill_ini_data();
        if (check_value(key)) return ini_data[key];
    }
    template <>
    int get_value(std::string key) {
        //fill_ini_data();
        if (check_value(key)) return std::stoi(ini_data[key]);
    }
    template <>
    double get_value(std::string key) {
        //fill_ini_data();
            if (check_value(key)) return std::atof(ini_data[key].c_str()); 

    }

};

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    
    ini_parser parser("ini.txt");
    if (parser.is_file_open) {

        auto value = parser.get_value<double>("Section1.var1");
        if (parser.is_value_found) std::cout << std::endl << "Значение запрошенного параметра равно " << value << std::endl;
    
    }
}
