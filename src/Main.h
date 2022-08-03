#include "PCH.h"
#include "Card.h"
#include "Deck.h"
#pragma once

namespace App
{
    void resetFile(std::string fileName);
    void ComputeHands(std::string fileName, Deck deck, int start, int end, long *handCount);
}

namespace Hand
{
    bool isEqual(std::vector<Card> hand1, std::vector<Card> hand2);
}