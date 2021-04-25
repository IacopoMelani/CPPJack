#include "CardBearer.h"

#define CHECK_VALID_SCORE                           \
    if (this->get_total_score() <= MAX_SCORE_LIMIT) \
    {                                               \
        return;                                     \
    }

CardBearer::CardBearer() : Deck()
{
#ifdef DEBUG
    std::cout << "++ CardBearer alloc" << std::endl;
#endif // DEBUG
}

CardBearer::~CardBearer()
{
#ifdef DEBUG
    std::cout << "-- CardBearer dealloc" << std::endl;
#endif // DEBUG
}

void CardBearer::add_card(Card *card, bool hide)
{
    Deck::add_card(card, hide);
    this->check_aces();
}

bool CardBearer::can_double() const
{
    return !this->is_blackjack() && this->get_total_cards() == CARD_LEN_TO_BLACKJACK && this->get_total_score() >= DOUBLE_MIN_LIMIT && this->get_total_score() <= DOUBLE_MAX_LIMIT;
}

void CardBearer::check_aces()
{
    CHECK_VALID_SCORE;
    for (auto card : this->cards)
    {
        CHECK_VALID_SCORE;
        card->mutate_ace();
    }
}

uint CardBearer::get_total_score(bool withHide) const
{
    uint current_score = 0;

    for (auto card : this->cards)
    {
        if (card->is_hide() && !withHide)
        {
            continue;
        }
        current_score += card->get_value();
    }

    return current_score;
}

bool CardBearer::is_blackjack() const
{
    return this->cards.size() == CARD_LEN_TO_BLACKJACK && this->get_total_score() == MAX_SCORE_LIMIT;
}

bool CardBearer::is_exceeded() const
{
    return this->get_total_score() > MAX_SCORE_LIMIT;
}

bool CardBearer::is_over() const
{
    return this->is_blackjack() || this->is_exceeded();
}

std::vector<Card *> CardBearer::return_cards()
{
    std::vector<Card *> cards;

    while (!this->cards.empty())
    {
        cards.push_back(this->draw_card());
    }

    return cards;
}

std::string CardBearer::sprint() const
{
    char buff[100];
    std::string buffAsStdStr = "";

    snprintf(buff, sizeof(buff), "Total score: %u, Total cards: %lu\n", this->get_total_score(), this->get_total_cards());

    buffAsStdStr.append(buff);

    for (auto card : this->cards)
    {
        if (card->is_hide())
        {
            buffAsStdStr.append("Hidden");
        }
        else
        {
            buffAsStdStr.append(card->sprint());
        }

        buffAsStdStr.append("\n");
    }

    return buffAsStdStr;
}