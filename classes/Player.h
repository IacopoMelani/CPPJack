#ifndef _PLAYER_H
#define _PLAYER_H

#include <iostream>
#include <vector>

#include "Card.h"
#include "CardBearer.h"
#include "Print.h"

#define INITIAL_BANK_ACCOUNT 5

class Player : public Print
{
protected:
    std::string name;
    uint bank_account = INITIAL_BANK_ACCOUNT;

public:
    Player(const std::string &name, uint bank_account = INITIAL_BANK_ACCOUNT);
    ~Player();

    uint get_bank_accout() const;
    std::string get_name() const;
    virtual std::string sprint() const;
};

#endif // _PLAYER_H