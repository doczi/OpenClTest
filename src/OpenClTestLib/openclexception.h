#ifndef OPENCLEXCEPTION_H
#define OPENCLEXCEPTION_H

#include <sstream>
#include <stdexcept>



class OpenClException: public std::runtime_error
{
public:
    OpenClException(const std::string& message):
        std::runtime_error(message)
    {}
    OpenClException(const std::string& message, int errorCode):
        std::runtime_error(message + " (" + toString(errorCode) + ")")
    {}
private:
    static std::string toString(int code) {
        std::ostringstream oss;
        oss << code;
        return oss.str();
    }
};



#endif // OPENCLEXCEPTION_H
