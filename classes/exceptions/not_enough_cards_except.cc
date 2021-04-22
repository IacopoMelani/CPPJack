#include "not_enough_cards_except.h"

NotEnoughCardsExecption::NotEnoughCardsExecption(const std::string &msg) : msg(msg), exception() {}

const char *NotEnoughCardsExecption::what() const noexcept
{
    return this->msg.c_str();
}