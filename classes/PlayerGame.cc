#include "PlayerGame.h"

#include <cmath>
#include <sstream>

#include "Dealer.h"
#include "cli/io.h"
#include "utils/color.h"
#include "utils/console.h"

PlayerGame::PlayerGame(Player *player, bool is_cpu) : CardBearer()
{
#ifdef DEBUG
    std::cout << "++ PlayerGame alloc" << std::endl;
#endif // DEBUG
    this->player = player;
    this->amount_bet = 0;
    this->is_cpu = is_cpu;
}

PlayerGame::~PlayerGame()
{
    delete this->player;

#ifdef DEBUG
    std::cout << "++ PlayerGame alloc" << std::endl;
#endif // DEBUG
}

bool PlayerGame::auto_play(Dealer *dealer)
{
    if (this->get_total_score() >= 17)
    {
        return false;
    }
    this->drawn_card_from_dealer(dealer);
    return true;
}

bool PlayerGame::can_double() const
{
    return CardBearer::can_double() && this->player->get_bank_account() >= this->amount_bet;
}

void PlayerGame::drawn_card_from_dealer(Dealer *dealer)
{
    this->add_card(dealer->deck_drawn_card());
}

std::string PlayerGame::get_game_options() const
{
    std::string options;

    options = R"(
Choose your move:
    1) Draw
    2) Stop)";

    if (this->can_double())
    {
        options.append(R"(
    3) Double)");
    }

    options.append("\n");

    return options;
}

std::string PlayerGame::get_player_name() const
{
    return this->player->get_name();
}

bool PlayerGame::is_cpu_player() const
{
    return this->is_cpu;
}

void PlayerGame::make_bet()
{
    std::ostringstream buffAsStdOStream;

    color::Modifier start = color::Modifier(color::Code::FG_GREEN);
    color::Modifier end = color::Modifier(color::Code::FG_DEFAULT);

    uint amount_bet;

    if (this->is_cpu)
    {
        amount_bet = 1;
    }
    else
    {
#ifdef AUTO
        amount_bet = 1;
#else
        buffAsStdOStream << "Insert amout bet, max availability is " << start << this->player->get_bank_account() << end << ": ";
        amount_bet = IO::ask_uint(buffAsStdOStream.str(), 1, this->player->get_bank_account());
#endif // AUTO
    }

    this->amount_bet = amount_bet;

    this->player->remove_money(amount_bet);
}

bool PlayerGame::match_end() const
{
    return this->player->get_bank_account() == 0;
}

void PlayerGame::play(Dealer *dealer)
{
    auto continue_step = true;

    while (!this->is_over() && continue_step)
    {
        if (this->is_cpu)
        {
            continue_step = this->auto_play(dealer);
        }
        else
        {
#ifdef AUTO
            continue_step = this->auto_play(dealer);
#else
            continue_step = this->play_step(dealer);
#endif // AUTO
        }

        console::clear();
        this->print();
    }
}

bool PlayerGame::play_step(Dealer *dealer)
{
    bool continue_step = true;
    auto res = IO::ask_from_options<int>(this->get_game_options());
    switch (res)
    {
    case 1:
        this->drawn_card_from_dealer(dealer);
        break;
    case 2:
        continue_step = false;
        break;
    case 3:
        this->drawn_card_from_dealer(dealer);
        this->player->remove_money(this->amount_bet);
        this->amount_bet *= 2;
        continue_step = false;
        break;
    }
    return continue_step;
}

void PlayerGame::result(bool win)
{
    if (win)
    {
        double amount_win = this->amount_bet * 2;

        if (this->is_blackjack())
        {
            amount_win = this->amount_bet + (this->amount_bet * (3 / 2));
            amount_win = std::round(amount_win);
        }

        this->player->add_money((uint)amount_win);
    }
    this->amount_bet = 0;
}

void PlayerGame::set_amount_bet(uint amount)
{
    this->amount_bet = amount;
}

std::string PlayerGame::sprint() const
{
    std::string buffAsStdStr = "";
    std::ostringstream buffAsStdOStrStream;

    color::Modifier start = color::Modifier(color::Code::FG_DEFAULT);
    color::Modifier end = color::Modifier(color::Code::FG_DEFAULT);

    if (!this->is_cpu)
    {
        start = color::Modifier(color::Code::FG_GREEN);
    }

    buffAsStdStr.append(this->player->sprint());

    buffAsStdStr.append("\n");

    buffAsStdStr.append(CardBearer::sprint());

    buffAsStdOStrStream << start << buffAsStdStr << end;

    return buffAsStdOStrStream.str();
}
//