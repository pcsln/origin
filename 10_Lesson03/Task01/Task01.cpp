#include <iostream>
#include <fstream> 

class LogCommand {
public:
    virtual ~LogCommand() = default;
    virtual void print(const std::string& message) = 0;
};

class LogConsol : public LogCommand {
    void print(const std::string& message) override {
        std::cout << message << std::endl;
    }
};

class LogFile : public LogCommand {
    void print(const std::string& message) override {
        std::ofstream file;
        file.open("log.txt");
        if (file.is_open()) {
            file << "Log message";
        }
        file.close();
    }
};

void print(LogCommand& command) {
    command.print("Log message");
};

int main()
{
    LogConsol logger;
    print(logger);

    LogFile flogger;
    print(flogger);
}

