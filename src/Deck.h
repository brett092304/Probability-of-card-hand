#include "PCH.h"
#include "Card.h"
#pragma once

class Deck
{
    public:
        Deck(std::vector<std::string> ranks, std::vector<std::string> suits, std::vector<int> values);
        Deck(std::vector<Card> cards);
        std::vector<Card> getDeck();
        void printDeck();
        Card dealCard();
        bool isEmpty();
        void refill();
        void empty();
        int getSize();

    private:
        std::vector<Card> deck;
        int deckSize;

};