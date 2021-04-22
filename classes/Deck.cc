#include "Deck.h"

#include <algorithm>
#include <chrono>
#include <random>

#include "Card.h"
#include "classes/exceptions/not_enough_cards_except.h"

Deck::Deck() : cards({})
{
#ifdef DEBUG
    std::cout << "++ Deck alloc" << std::endl;
#endif // DEBUG
}

Deck::~Deck()
{
    for (auto card : this->cards)
    {
        delete card;
    }
#ifdef DEBUG
    std::cout << "-- Deck dealloc" << std::endl;
#endif // DEBUG
}

void Deck::add_card(Card *card, bool hide)
{
    if (hide)
    {
        card->set_hide(hide);
    }
    this->cards.push_back(card);
}

Card *Deck::draw_card()
{
    if (this->cards.empty())
    {
        throw NotEnoughCardsExecption();
    }

    auto card = this->cards.at(0);

    this->cards.erase(this->cards.begin());

    return card;
}

size_t Deck::get_total_cards() const
{
    return this->cards.size();
}

void Deck::init_deck()
{
    for (auto seed : allSeeds)
    {
        int indexSymbol = 0;
        for (auto symbol : allSymbols)
        {
            unsigned int value = allValue[indexSymbol];
            Card *card = new Card(seed, symbol, value);
            this->add_card(card);
            indexSymbol++;
        }
    }
}

void Deck::shuffle()
{
    unsigned seed = std::chrono::system_clock::now()
                        .time_since_epoch()
                        .count();

    std::shuffle(std::begin(this->cards), std::end(this->cards), std::default_random_engine(seed));
}