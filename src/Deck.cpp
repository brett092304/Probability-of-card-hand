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
    deckSize = deck.size();
}

Deck::Deck(std::vector<Card> cards)
{
    deck = cards;
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

Card Deck::dealCard()
{
    deck.front() = deck.back();
    deckSize--;
}

int Deck::getSize()
{
    return deckSize;
}

bool Deck::isEmpty()
{
    if (deckSize <= 0)
    {
        return true;
    }
    return false;
}

void Deck::refill()
{
    deckSize = deck.size();
}

void Deck::empty()
{
    deckSize = 0;
}