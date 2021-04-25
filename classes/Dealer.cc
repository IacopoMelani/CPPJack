#include "Dealer.h"

#include <sstream>

#include "classes/exceptions/not_enough_cards_except.h"

#include "cli/io.h"
#include "utils/color.h"
#include "utils/console.h"

Dealer::Dealer() : CardBearer()
{
#ifdef DEBUG
    std::cout << "++ Dealer alloc" << std::endl;
#endif // DEBUG
    this->deck = new Deck();
    this->deck->init_deck();
    this->players_game = {};
}

Dealer::~Dealer()
{
    for (auto player_game : this->players_game)
    {
        delete player_game;
    }

    delete this->deck;

#ifdef DEBUG
    std::cout << "-- Dealer dealloc" << std::endl;
#endif // DEBUG
}

void Dealer::calc_results()
{
    auto dealer_total_score = this->get_total_score();

    bool player_win = false;

    auto iterator = std::begin(this->players_game);

    while (iterator != std::end(this->players_game))
    {
        auto player_game = iterator.base();

        uint player_game_total_score = (*player_game)->get_total_score();

        if (player_game_total_score > MAX_VALID_SCORE)
        {
            player_win = false;
            std::cout << (*player_game)->get_player_name() << " has lost, over " << MAX_VALID_SCORE << std::endl;
        }
        else if (dealer_total_score > MAX_VALID_SCORE)
        {
            player_win = true;
            std::cout << (*player_game)->get_player_name() << " won, the dealer went over " << MAX_VALID_SCORE << std::endl;
        }
        else if (player_game_total_score <= dealer_total_score)
        {
            player_win = false;
            std::cout << (*player_game)->get_player_name() << " has lost, the dealer wins" << std::endl;
        }
        else
        {
            player_win = true;
            std::cout << (*player_game)->get_player_name() << " wins with " << player_game_total_score << ", the dealer only made " << dealer_total_score << std::endl;
        }

        (*player_game)->result(player_win);

        if ((*player_game)->match_end())
        {
            PlayerGame *toDelete = this->players_game.at(iterator - this->players_game.begin());
            this->retake_cards(toDelete->return_cards());

            iterator = this->players_game.erase(iterator);
            delete toDelete;
        }
        else
        {
            ++iterator;
        }
    }
}

void Dealer::deal_initial_cards()
{
    bool first_card_drawn = false;

    for (int i = 0; i < 2; i++)
    {
        if (!first_card_drawn)
        {
            this->add_card(this->deck->draw_card(), true);
        }
        else
        {
            this->add_card(this->deck->draw_card());
        }

        for (auto player_game : this->players_game)
        {
            player_game->add_card(this->deck->draw_card());
        }

        first_card_drawn = true;
    }
}

Card *Dealer::deck_drawn_card()
{
    return this->deck->draw_card();
}
uint Dealer::get_max_num_players()
{
    return MAX_NUM_PLAYERS;
}

uint Dealer::get_real_players_count()
{
    uint count = 0;

    for (auto player_game : this->players_game)
    {
        if (!player_game->is_cpu_player())
        {
            count++;
        }
    }

    return count;
}

void Dealer::init_players(const unsigned int nums_players)
{
    if (this->players_game.size() > 0 || nums_players == 0 || nums_players > MAX_NUM_PLAYERS)
    {
        return;
    }

    bool is_cpu = false;

    for (int i = 0; i < nums_players; i++)
    {
        Player *player;

        if (!is_cpu)
        {
            std::string name;

#ifdef AUTO
            name = "John";
#else
            name = IO::ask_string("Insert your name: ");
#endif // AUTO
            console::clear();

            player = new Player(name);
        }
        else
        {
            std::ostringstream tempName;

            tempName << "Cpu " << i;

            player = new Player(tempName.str());
        }

        auto player_game = new PlayerGame(player, is_cpu);

        this->players_game.push_back(player_game);

        is_cpu = true;
    }
}

void Dealer::play()
{
    bool continue_play = true;

#ifdef AUTO

    int counter = 0;

#endif // AUTO

    do
    {
        try
        {
            console::clear();

            this->prepare_player_games();

            this->deck->shuffle();

            this->deal_initial_cards();

            console::clear();

            this->print_game();

            for (auto player_game : this->players_game)
            {
                player_game->play(this);
            }

            while (this->get_total_score(true) < DEALER_MIN_SCORE_TO_STOP)
            {
                auto card = this->deck_drawn_card();
                this->add_card(card);
            }

            this->reveal_hidden_cards();

            console::clear();
        }
        catch (const NotEnoughCardsExecption &e)
        {
            std::cerr << e.what() << std::endl;
            return;
        }

        this->print_game();

        this->calc_results();

        this->retake_cards_from_players_game();

        if (this->players_game.size() == 0)
        {
#ifndef AUTO
            IO::wait_action("The game is over. All players have lost.");
#endif
            continue_play = false;
        }
        else if (this->get_real_players_count() > 0)
        {
#ifdef AUTO
            continue_play = true;
#else
            continue_play = IO::ask_bool("Another match?");
#endif // AUTO
        }
        else
        {
#ifdef AUTO
            continue_play = true;
#else
            continue_play = IO::ask_bool("You are out. do you want to continue watching the game?");
#endif // AUTO
        }

#ifdef AUTO
        ++counter;

#endif // AUTO

    } while (continue_play);

#ifdef AUTO
    std::cout << "Auto mode terminated, total games: " << counter << std::endl;
#endif // AUTO
}

void Dealer::prepare_player_games()
{
    for (auto player_game : this->players_game)
    {
        player_game->make_bet();
    }
}

void Dealer::print_game() const
{
    this->print();
    this->print_players();
}

void Dealer::print_players() const
{
    auto players_len = this->players_game.size();

    if (players_len > 1)
    {
        std::cout
            << "Total players in game: " << players_len << std::endl
            << std::endl;
    }

    for (auto player_game : this->players_game)
    {
        player_game->print();
    }
}

void Dealer::retake_cards(std::vector<Card *> cards)
{
    for (auto card : cards)
    {
        this->deck->add_card(card);
    }
}

void Dealer::retake_cards_from_players_game()
{
    for (auto player_game : this->players_game)
    {
        auto cards = player_game->return_cards();
        this->retake_cards(cards);
    }

    while (!this->cards.empty())
    {
        this->deck->add_card(this->draw_card());
    }
}

void Dealer::reveal_hidden_cards()
{
    for (auto card : this->cards)
    {
        card->set_hide(false);
    }
}

std::string Dealer::sprint() const
{
    std::string buffAsStdStr = "Dealer\n";
    std::ostringstream buffAsStdOStrStream;

    buffAsStdStr.append(CardBearer::sprint());
    color::Modifier start = color::Modifier(color::Code::FG_RED);
    color::Modifier end = color::Modifier(color::Code::FG_DEFAULT);

    buffAsStdOStrStream << start << buffAsStdStr << end;

    return buffAsStdOStrStream.str();
}
