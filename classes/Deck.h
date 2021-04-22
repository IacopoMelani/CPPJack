#ifndef _DECK_H
#define _DECK_H

#include "Card.h"

#include <iostream>
#include <vector>

class Deck
{
protected:
    std::vector<Card *> cards;

public:
    Deck();
    ~Deck();

    virtual void add_card(Card *card, bool hide = false);
    virtual Card *draw_card();
    size_t get_total_cards() const;
    void init_deck();
    virtual void shuffle();
};

#endif // _DECK_H