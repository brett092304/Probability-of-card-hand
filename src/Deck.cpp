#include "Deck.h"

Deck::Deck(std::vector<std::string> ranks, std::vector<std::string> suits, std::vector<int> values)
{
    for (int i = 0; i < ranks.size(); i++)
    {
        for (int j = 0; j < suits.size(); j++)
        {
            deck.push_back(Card(ranks[i], suits[j], values[i]));
        }
    }
}

std::vector<Card> Deck::getDeck()
{
    return deck;
}

void Deck::printDeck()
{
    for (int i = 0; i < deck.size(); i++)
    {
        std::cout << deck.at(i).getCard() << std::endl;
    }
}