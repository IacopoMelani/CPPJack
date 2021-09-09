#ifndef _INVALID_VALUE_PASSED_EXCEPT_H
#define _INVALID_VALUE_PASSED_EXCEPT_H

#include <exception>
#include <string>

#include "cppjack_std_except.h"

namespace IO
{
    class InvalidValuePassedException : public CPPJackStdExcept
    {
    public:
        InvalidValuePassedException(const std::string &msg = "Invalid value passed");
    };
}

#endif // _INVALID_VALUE_PASSED_EXCEPT_H
