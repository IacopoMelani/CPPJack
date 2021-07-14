#include "Card.h"
#include "CardBearer.h"

#ifdef ACE
#undef ACE
#endif // ACE

#define ACE "Ace"

std::array<unsigned int, 13> allValue = {11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10};

std::array<std::string, 4> allSuits = {"diamonds", "clubs", "hearts", "spades"};

std::array<std::string, 13> allSymbols = {ACE, "Two", "Three", "Four", "Five", "Six", "Seven", "Height", "Nine", "Ten", "Jack", "Queen", "King"};

Card::Card(const std::string &suit, const std::string &symbol, unsigned int value) : suit(suit),
                                                                                     symbol(symbol),
                                                                                     value(value),
                                                                                     hide(false)
{
#ifdef DEBUG
    std::cout << "++ Card alloc " << this->sprint() << std::endl;
#endif // DEBUG
}

Card::~Card()
{
#ifdef DEBUG
    std::cout << "-- Card dealloc " << this->sprint() << std::endl;
#endif // DEBUG
}

unsigned int Card::get_value()
{
    return this->value;
}

bool Card::is_ace()
{
    return this->symbol == ACE;
}

bool Card::is_hide()
{
    return this->hide;
}

bool Card::mutate_ace()
{
    if (!this->is_ace())
    {
        return false;
    }

    this->value = 1;

    return true;
}

void Card::set_hide(bool value)
{
    this->hide = value;
}

std::string Card::sprint() const
{
    char buff[100];
    snprintf(buff, sizeof(buff), "%s of %s", this->symbol.c_str(), this->suit.c_str());
    std::string buffAsStdStr = buff;
    return buffAsStdStr;
}