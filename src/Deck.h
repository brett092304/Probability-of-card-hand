#include "PCH.h"
#include "Card.h"
#pragma once

class Deck
{
    public:
        Deck(std::vector<std::string> ranks, std::vector<std::string> suits, std::vector<int> values);
        std::vector<Card> getDeck();
        void printDeck();

    private:
        std::vector<Card> deck;

};