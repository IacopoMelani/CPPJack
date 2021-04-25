#ifndef _DEALER_H
#define _DEALER_H

#include <vector>

#include "CardBearer.h"
#include "Deck.h"
#include "PlayerGame.h"
#include "Print.h"

#define DEALER_MIN_SCORE_TO_STOP 17

#define MAX_VALID_SCORE 21
#define MAX_NUM_PLAYERS 7

class Dealer : public CardBearer
{
protected:
    std::vector<PlayerGame *> players_game;
    Deck *deck;

    void calc_results();
    void deal_initial_cards();
    uint get_real_players_count();
    void reveal_hidden_cards();
    void retake_cards(std::vector<Card *> cards);
    void retake_cards_from_players_game();

public:
    Dealer();
    ~Dealer();

    Card *deck_drawn_card();
    static uint get_max_num_players();
    void init_players(const unsigned int nums_players);
    void play();
    void prepare_player_games();
    void print_game() const;
    void print_players() const;
    virtual std::string sprint() const override;
};

#endif // _DEALER_H