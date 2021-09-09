#ifndef _NOT_ENOUGH_CARDS_EXCEPT_H
#define _NOT_ENOUGH_CARDS_EXCEPT_H

#include <exception>
#include <string>

#include "cppjack_std_except.h"

class NotEnoughCardsExecption : public CPPJackStdExcept
{
public:
    NotEnoughCardsExecption(const std::string &msg = "Not enough cards");
};

#endif // _NOT_ENOUGH_CARDS_EXCEPT_H