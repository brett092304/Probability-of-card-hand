#include "PCH.h"
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