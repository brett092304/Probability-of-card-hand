#include "PCH.h"
#include "Card.h"

struct Hand
{
    public:
        Hand(std::vector<Card> hand);
        std::vector<Card> getHand();

    private:
        std::vector<Card> hand;
};