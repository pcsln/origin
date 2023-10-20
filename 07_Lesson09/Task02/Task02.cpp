#include <iostream>
#include <string>


class big_integer
{
    char* cstring;  
                    
public:
    explicit big_integer(const char* s = "") : cstring(nullptr)
    {
        if (s)
        {
            std::size_t n = std::strlen(s) + 1;
            cstring = new char[n];      
            std::memcpy(cstring, s, n); 
            //std::cout << "NEW " << std::endl;
        }
    }
    auto get_value() {
        return cstring;
    }
    auto get_value(int i) {
        return cstring[i];
    }
    ~big_integer()
    {
        //std::cout << "Deleted" << std::endl;
        delete[] cstring; 
    }

    big_integer(const big_integer& bi) 
        : big_integer(bi.cstring) {}

    big_integer(big_integer&& bi) noexcept 
        : cstring(std::exchange(bi.cstring, nullptr)) {}

    big_integer& operator=(const big_integer& bi) 
    {
        return *this = big_integer(bi);
    }

    big_integer& operator=(big_integer&& bi) noexcept 
    {
        std::swap(cstring, bi.cstring);
        return *this;
    }

    std::string summa(const char* cstring, const char* bstring) {

        int c_len = strlen(cstring);
        int b_len = strlen(bstring);

        int n = 0;
        int k_c = 0;
        int k_b = 0;
        c_len >= b_len ? n = c_len : n = b_len;
        c_len >= b_len ? k_b = c_len - b_len : k_c = b_len - c_len;

        std::string str = "";
        char c_string_i = ' ';
        char b_string_i = ' ';
        int digit = 0;
        for (int i = n - 1; i >= 0; --i) {
            i - k_c < 0 ? c_string_i = '0' : c_string_i = cstring[i - k_c];
            i - k_b < 0 ? b_string_i = '0' : b_string_i = bstring[i - k_b];


            int sum = c_string_i - 48 + b_string_i - 48 + digit;
            int rem = sum % 10;
            digit = sum / 10;

            str.insert(0, std::to_string(rem));

        }
        if (digit) { str.insert(0, std::to_string(digit)); }

        return str;
    }

    std::string multi(const char* cstring, int n) {
        std::string result = "0";
        int c_len = strlen(cstring);
        int k = 0;

        while (n > 0)
        {
            std::string intermediate_result = "";
            int multiplier = n % 10;
            n /= 10;
            int digit = 0;


            for (auto i = c_len - 1; i >= 0; --i) {
                int sum = (cstring[i] - 48) * multiplier + digit;
                int rem = sum % 10;
                digit = sum / 10;

                intermediate_result.insert(0, std::to_string(rem));

            }

            if (digit > 0) {
                intermediate_result.insert(0, std::to_string(digit));
            }

            for (auto i = 0; i < k; ++i) {
                intermediate_result.append("0");
            }
            ++k;

            result = summa(result.c_str(), intermediate_result.c_str());
        }
        return result;
    }

    big_integer operator+(big_integer& bi) {

        return std::move(big_integer(summa(cstring, bi.get_value()).c_str()));
    }

    big_integer operator*(int n) {

        if (n == 0) {
            return std::move(big_integer("0"));
        }

        return std::move(big_integer(multi(cstring, n).c_str()));
    }

    friend std::ostream& operator<<(std::ostream& os, big_integer& bi);
};

std::ostream& operator<<(std::ostream& os, big_integer& bi)
{
    os << bi.get_value() << std::endl;
    return os;
}


int main()
{
    auto number1 = big_integer("114575");
    auto number2 = big_integer("78524");

    auto result = number1 + number2;

    std::cout << result  << std::endl;

    auto result2 = result * 193099;

    std::cout << result2;


}