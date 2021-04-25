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

void Player::add_money(uint money)
{
    this->bank_account += money;
}

uint Player::get_bank_account() const
{
    return this->bank_account;
}

std::string Player::get_name() const
{
    return this->name;
}

bool Player::remove_money(uint money)
{
    if (this->bank_account < money)
    {
        return false;
    }

    this->bank_account -= money;

    return true;
}

std::string Player::sprint() const
{
    char buff[100];
    snprintf(buff, sizeof(buff), "%s, current bank account: %u", this->name.c_str(), this->bank_account);
    std::string buffAsStdStr = buff;
    return buffAsStdStr;
}
