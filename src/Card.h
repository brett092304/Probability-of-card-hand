#include "PCH.h"
#pragma once

class Card
{
    public:
        Card(std::string rank, std::string suit, int value);
        std::string getCard();

    private:
        std::string suit;
        std::string rank;
        int value;
};