#ifndef _PLAYER_GAME_H
#define _PLAYER_GAME_H

#include "CardBearer.h"
#include "Player.h"
#include "Print.h"

class Dealer;

class PlayerGame : public CardBearer
{
private:
    bool is_cpu;
    Player *player;
    uint amount_bet;

    bool auto_play(Dealer *dealer);
    void drawn_card_from_dealer(Dealer *dealer);
    bool play_step(Dealer *dealer);

public:
    PlayerGame(Player *player, bool is_cpu = false);
    ~PlayerGame();

    virtual bool can_double() const override;
    std::string get_game_options() const;
    std::string get_player_name() const;
    bool is_cpu_player() const;
    void make_bet();
    bool match_end() const;
    void play(Dealer *delaer);
    void result(bool win);
    void set_amount_bet(uint amount);
    virtual std::string sprint() const override;
};

enum class GameOption
{
    CARD = 1,
    STAY,
    DOUBLE
};

#endif // _PLAYER_GAME_H