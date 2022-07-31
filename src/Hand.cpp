#include "Hand.h"

Hand::Hand(std::vector<Card> hand)
{
    this->hand = hand;   
}

std::vector<Card> Hand::getHand()
{
    return hand;
}