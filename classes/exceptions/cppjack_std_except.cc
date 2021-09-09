#include "cppjack_std_except.h"

CPPJackStdExcept::CPPJackStdExcept(const std::string &msg) : msg(msg), exception() {}

const char *CPPJackStdExcept::what() const noexcept
{
    return this->msg.c_str();
}