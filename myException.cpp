#ifndef EXCEPTIONS_CPP
#define EXCEPTIONS_CPP


#include <exception>


class myException : public std::exception {
public:
public:
    enum class ExceptionType {
        ExceededMaxValue,
        WrongValue,
        WrongName,
        WrongOrder,
        WrongId,
        FileNotFound,
        WrongTableNum
    };

    myException(ExceptionType type)
    : m_type(type) {}

    const char* what() const noexcept override {
        switch (m_type) {
            case ExceptionType::ExceededMaxValue:
                return "Wrong time input. Right input is: XX:XX, where hours are in range of 0-23 and minutes are in range 0-59.";
            case ExceptionType::WrongValue:
                return "Value should be > 1 for number of tables and > 0 for cost for an hour.";
            case ExceptionType::WrongName:
                return "Clients name does not match the pattern";
            case ExceptionType::WrongOrder:
                return "Actions should be ordered by time";
            case ExceptionType::WrongId:
                return "There is no such id in the list";
            case ExceptionType::FileNotFound:
                return "There is no such file";
            case ExceptionType::WrongTableNum:
                return "There are no such table";
            default:
                return "Unknown exception";
        }
    }

private:
    ExceptionType m_type;
};

#endif