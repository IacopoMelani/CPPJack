
#include "invalid_value_passed_except.h"

IO::InvalidValuePassedException::InvalidValuePassedException(const std::string &msg) : CPPJackStdExcept(msg) {}
