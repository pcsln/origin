#include <fstream>
#include <iostream>

class LogMessage {
public:
    enum class Type {
        FatalError,
        Error,
        Warning,
        Unknown,
    };
    virtual Type type() const = 0;
    virtual const char* message() const = 0;
};

class LogHandler {
public:
    explicit LogHandler(std::unique_ptr<LogHandler> next) : next_(std::move(next)) {}
    virtual ~LogHandler() = default;
    void receiveLog(const LogMessage& msg) {
        if (handleLog(msg)) {
            return;
        }
        if (!next_) {
            throw std::runtime_error("Error: Message should be handled!");
        }
        next_->receiveLog(msg);
    }
private:
    virtual bool handleLog(const LogMessage& msg) = 0;

    std::unique_ptr<LogHandler> next_;
};

class FatalHandler : public LogHandler {
public:
    using LogHandler::LogHandler;
private:
    bool handleLog(const LogMessage& msg) override {
        if (msg.type() != LogMessage::Type::FatalError) {
            return false;
        }
        throw std::runtime_error("Fatal error");
        return true;
    }
};

class ErrorHandler : public LogHandler {
public:
    using LogHandler::LogHandler;
private:
    bool handleLog(const LogMessage& msg) override {
        if (msg.type() != LogMessage::Type::Error) {
            return false;
        }
        
        std::ofstream file;
        file.open("logerror.txt");
        if (file.is_open()) {
            file << msg.message();
        }
        file.close();

        std::cout << "Error message : " << msg.message() << " wrote to a file." << std::endl;

        return true;
    }
};

class WarningHandler : public LogHandler {
public:
    using LogHandler::LogHandler;
private:
    bool handleLog(const LogMessage& msg) override {
        if (msg.type() != LogMessage::Type::Warning) {
            return false;
        }
        std::cout << "Warning log message : " << msg.message() << std::endl;
        return true;
    }
};

class UnknownHandler : public LogHandler {
public:
    using LogHandler::LogHandler;
private:
    bool handleLog(const LogMessage& msg) override {
        if (msg.type() != LogMessage::Type::Unknown) {
            return false;
        }
        throw std::domain_error(msg.message());
        return true;
    }
};

class FatalMessage : public LogMessage {
public:
    Type type() const override { return Type::FatalError; }
    const char* message() const override {
        return nullptr;
    }
};
class ErrorMessage : public LogMessage {
public:
    Type type() const override { return Type::Error; }
    const char* message() const override {
        return "Error message";
    }
};
class WarningMessage : public LogMessage {
public:
    Type type() const override { return Type::Warning; }
    const char* message() const override {
        return "Warning message";
    }
};
class UnknownMessage : public LogMessage {
public:
    Type type() const override { return Type::Unknown; }
    const char* message() const override {
        return "Unkown Message";
    }
};

int main()
{

    auto fatal_handler = std::make_unique<FatalHandler>(nullptr);
    auto error_handler = std::make_unique<ErrorHandler>(std::move(fatal_handler));
    auto warning_handler = std::make_unique<WarningHandler>(std::move(error_handler));
    auto unknown_handler = std::make_unique<UnknownHandler>(std::move(warning_handler));


    try {
        unknown_handler->receiveLog(WarningMessage());
        unknown_handler->receiveLog(ErrorMessage());
        unknown_handler->receiveLog(UnknownMessage());
        unknown_handler->receiveLog(FatalMessage());
    }
    catch (const std::domain_error& e) {
        std::cout << e.what() << std::endl;
    }
}
