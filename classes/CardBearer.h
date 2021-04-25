#ifndef _CARD_BEARER_H
#define _CARD_BEARER_H

#include "Card.h"
#include "Deck.h"
#include "Print.h"

#define MAX_SCORE_LIMIT 21
#define CARD_LEN_TO_BLACKJACK 2
#define DOUBLE_MAX_LIMIT 11
#define DOUBLE_MIN_LIMIT 9

class CardBearer : public Deck,
                   public Print
{
private:
    void check_aces();
    unsigned int get_total_score_raw() const;

public:
    CardBearer();
    ~CardBearer();

    virtual void add_card(Card *card, bool hide = false) override;
    virtual bool can_double() const;
    uint get_total_score(bool withHide = false) const;
    bool is_blackjack() const;
    bool is_exceeded() const;
    bool is_over() const;
    std::vector<Card *> return_cards();
    virtual std::string sprint() const override;
};

#endif // _CARD_BEARER_H