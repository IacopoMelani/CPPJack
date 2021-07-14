#ifndef _CARD_H
#define _CARD_H

#include <array>
#include <iostream>

#include "Print.h"

extern std::array<unsigned int, 13> allValue;
extern std::array<std::string, 4> allSuits;
extern std::array<std::string, 13> allSymbols;

class Card : public Print
{
protected:
    std::string suit;
    std::string symbol;
    unsigned int value;
    bool hide;

public:
    Card(const std::string &suit, const std::string &symbol, unsigned int value);
    ~Card();

    unsigned int get_value();
    bool is_ace();
    bool is_hide();
    bool mutate_ace();
    void set_hide(bool value);
    std::string sprint() const;
};

#endif // _CARD_H
