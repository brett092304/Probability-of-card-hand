#include "Card.h"

Card::Card(std::string rank, std::string suit, int value)
{
    this->rank = rank;
    this->suit = suit;
    this->value = value;
}

Card::Card(){}

std::string Card::getCard()
{
    return rank + " " + suit + " " + std::to_string(value);
}