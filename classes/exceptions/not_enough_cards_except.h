#ifndef _NOT_ENOUGH_CARDS_EXCEPT_H
#define _NOT_ENOUGH_CARDS_EXCEPT_H

#include <exception>
#include <string>

class NotEnoughCardsExecption : public std::exception
{
protected:
    std::string msg;

public:
    NotEnoughCardsExecption(const std::string &msg = "Not enough cards");

    virtual const char *what() const noexcept override;
};

#endif // _NOT_ENOUGH_CARDS_EXCEPT_H