#include "Deck.h"
//#include "Card.h"
#include "Hand.h"


int main()
{
    std::vector<std::string> ranks = {"Ace", "King", "Queen", "Jack", "10", "9", "8", "7", "6", "5", "4", "3", "2"};
    std::vector<int> values = {11, 10, 10, 10, 10, 9, 8, 7, 6, 5, 4, 3, 2};
    std::vector<std::string> suits = {"Clubs", "Diamonds", "Spades", "Hearts"};

    Deck deck(ranks, suits, values);

    deck.printDeck();
    std::cout << deck.getDeck().size() << std::endl;
    std::vector<Card> cards = deck.getDeck();

    std::deque<Hand> hands;

    for (int i = 0; i < deck.getDeck().size(); i++)
    {
        std::vector<Card> semiHand;
        for (int j = 0; j < 5; j++)
        {
            semiHand.push_back(cards.at(i));
        }
        hands.push_back(Hand(semiHand));
        semiHand.clear();
    }

    for (int i = 0; i < hands.size(); i++)
    {
        for (int j = 0; j < hands.at(i).getHand().size(); j++)
        {
            std::cout << hands.at(i).getHand().at(j).getCard() << std::endl;
        }
        std::cout << "\n";
    }
    return 0;
}