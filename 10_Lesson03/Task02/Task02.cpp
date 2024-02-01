#include <iostream>
#include <vector>
#include <fstream>

class Observer {
public:
    virtual void onWarning(const std::string& message) {}
    virtual void onError(const std::string& message) {}
    virtual void onFatalError(const std::string& message) {}
};

class Warning_Observer : public Observer{
    void onWarning(const std::string& message) override {
        std::cout << "Warning_Observer : " << message << std::endl;
    }
};

class Error_Observer : public Observer {
    virtual void onError(const std::string& message) override{
        std::ofstream file;
        file.open("log.txt");
        if (file.is_open()) {
            file << message;
        }
        file.close();

        std::cout << "Error_Observer : wrote " << message << " to a file" << std::endl;
    }
};

class FatalError_Observer : public Observer {
    virtual void onFatalError(const std::string& message) override {
        std::cout << "FatalError_Observer : " << message << std::endl;

        std::ofstream file;
        file.open("fatalerror.txt");
        if (file.is_open()) {
            file << message;
        }
        file.close();

        std::cout << "FatalError_Observer : wrote " << message << " to a file" << std::endl;
    }
};


class Observed {
public:

    void warning(const std::string& message) const {
        std::cout << "Logger : " << message << std::endl;
        for (auto it : observers) {
            it->onWarning(message);
        }
    };

    void error(const std::string& message) const {
        std::cout << "Logger : " << message << std::endl;
        for (auto it : observers) {
            it->onError(message);
        }
    };

    void fatalError(const std::string& message) const {
        std::cout << "Logger : " << message << std::endl;
        for (auto it : observers) {
            it->onFatalError(message);
        }
    };

    void AddObserver(Observer* observer) {
        observers.push_back(observer);
    }
    void RemoveObserver(Observer* observer) {
        auto it = std::remove(observers.begin(), observers.end(), observer);
        observers.erase(it, observers.end());
    }
private:
    std::vector<Observer*> observers;
};

int main()
{
    Observed logger;
    Warning_Observer* wo = new Warning_Observer;
    Error_Observer* eo = new Error_Observer;
    FatalError_Observer* fo = new FatalError_Observer;
    logger.AddObserver(wo);
    logger.AddObserver(eo);
    logger.AddObserver(fo);

    logger.warning("warning message");
    logger.error("error message");
    logger.fatalError("fatal error message");

    logger.RemoveObserver(wo);
    logger.RemoveObserver(eo);
    logger.RemoveObserver(fo);
}


