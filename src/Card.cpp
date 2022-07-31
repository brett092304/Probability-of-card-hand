#include "Card.h"

Card::Card(std::string rank, std::string suit, int value)
{
    this->rank = rank;
    this->suit = suit;
    this->value = value;
}

std::string Card::getCard()
{
    return this->rank + " of " + this->suit + " Value = " + std::to_string(this->value);
}