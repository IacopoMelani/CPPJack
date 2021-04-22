#include "Player.h"

Player::Player(const std::string &name, uint bank_account) : name(name), bank_account(bank_account)
{
#ifdef DEBUG
    std::cout << "++ Player alloc" << std::endl;
#endif // DEBUG
}

Player::~Player()
{
#ifdef DEBUG
    std::cout << "-- Player dealloc" << std::endl;
#endif // DEBUG
}

uint Player::get_bank_accout() const
{
    return this->bank_account;
}

std::string Player::get_name() const
{
    return this->name;
}

std::string Player::sprint() const
{
    char buff[100];
    snprintf(buff, sizeof(buff), "%s, current bank account: %u", this->name.c_str(), this->bank_account);
    std::string buffAsStdStr = buff;
    return buffAsStdStr;
}
