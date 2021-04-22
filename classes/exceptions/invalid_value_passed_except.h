#ifndef _INVALID_VALUE_PASSED_EXCEPT_H
#define _INVALID_VALUE_PASSED_EXCEPT_H

#include <exception>
#include <string>

namespace IO
{
    class InvalidValuePassedException : public std::exception
    {
    protected:
        std::string msg;

    public:
        InvalidValuePassedException(const std::string &msg = "Invalid value passed");
        virtual const char *what() const noexcept override;
    };
}

#endif // _INVALID_VALUE_PASSED_EXCEPT_H
