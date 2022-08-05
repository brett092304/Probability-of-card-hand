#include "Main.h"

bool Hand::isEqual(std::vector<Card> hand1, std::vector<Card> hand2)
{
    bool handMatches = false;
    for (int i = 0; i < hand1.size(); i++)
    {
        bool foundMatch = false;
        for (int j = 0; j < hand2.size(); j++)
        {
            if (hand1.at(i).getCard() == hand2.at(j).getCard())
            {
                foundMatch = true;
            }
        }
        if (!foundMatch)
        {
            handMatches = false;
            break;
        }
        else
        {
            handMatches = true;
        }
    }
    return handMatches;
}

void Hand::addHand(std::vector<Card> &hand, std::deque<std::vector<Card>> &hands, int &count, int &counter, int cardsPerHand)
{
    while(hand.size() > cardsPerHand)
    {
        hand.front() = hand.back();
        hand.pop_back();
    }
    bool handMatches = false;
    /*for (int z = 0; z < hands.size(); z++)
    {
        if (Hand::isEqual(hand, hands.at(z)))
        {
            handMatches = true;
            hand.clear();
            counter = 0;
            break;
        }
    }*/
    if (!handMatches)
    {
        count++;
        hands.push_back(hand);
        hand.clear();
        counter = 0;
        /*for (int a = 0; a < hands.at(hands.size() -1).size(); a++)
        {
            std::cout << hands.at(hands.size() -1).at(a).getCard() << std::endl;
        }
        std::cout << "\n";*/
    }
}