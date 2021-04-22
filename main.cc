
#include <iostream>

#include "classes/Dealer.h"
#include "cli/io.h"
#include "utils/console.h"

int main()
{
    console::clear();

    console::show_title();

    Dealer *dealer = new Dealer();

    uint num_players;

#ifdef AUTO
    num_players = 4;
#else
    num_players = IO::ask_uint("Insert nums player: ", 1, Dealer::get_max_num_players());
#endif // AUTO

    dealer->init_players(num_players);

    dealer->play();

    delete dealer;
}