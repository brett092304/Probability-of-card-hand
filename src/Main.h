#include "PCH.h"
#include "Card.h"
#include "Deck.h"
#pragma once

namespace App
{
    void resetFile(std::string fileName);
    void ComputeHands(std::vector<Deck> &decks, long *handsCounted);
}

namespace Hand
{
    bool isEqual(std::vector<Card> hand1, std::vector<Card> hand2);
    void addHand(std::vector<Card> &hand, std::deque<std::vector<Card>> &hands, int &count, int &counter, int cardsPerHand);
}