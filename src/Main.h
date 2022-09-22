#include "PCH.h"
#include "Card.h"
#include "Deck.h"
#pragma once

namespace App
{
    void resetFile(std::string fileName);
    void ComputeHands(std::vector<Deck> &decks, long *handsCounted, int fileNum);
    void analyzeHands(std::deque<std::vector<Card>> &hands, int start, int end, int fileNum);
}

namespace Hand
{
    bool isEqual(std::vector<Card> hand1, std::vector<Card> hand2);
    bool isExact(std::vector<Card> hand1, std::vector<Card> hand2);
    bool hasDuplicates(std::vector<Card> hand);
    void addHand(std::vector<Card> &hand, std::deque<std::vector<Card>> &hands, int &count, int &counter, int cardsPerHand);
}