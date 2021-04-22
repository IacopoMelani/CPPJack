
#include "invalid_value_passed_except.h"

IO::InvalidValuePassedException::InvalidValuePassedException(const std::string &msg) : msg(msg), exception() {}

const char *IO::InvalidValuePassedException::what() const noexcept
{
    return this->msg.c_str();
}
