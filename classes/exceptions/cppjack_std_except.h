#ifndef _CPPJACK_STD_EXCEPT_H
#define _CPPJACK_STD_EXCEPT_H

#include <exception>
#include <string>

class CPPJackStdExcept : public std::exception
{
protected:
    std::string msg;

public:
    CPPJackStdExcept(const std::string &msg);

    virtual const char *what() const noexcept override;
};

#endif // _CPPJACK_STD_EXCEPT_H