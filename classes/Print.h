#ifndef _PRINT_H
#define _PRINT_H

#include <iostream>

class Print
{
public:
    virtual void print() const;
    virtual std::string sprint() const = 0;
};

#endif // _PRINT_H