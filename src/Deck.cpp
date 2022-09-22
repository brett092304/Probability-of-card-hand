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
    deckiter = deck.begin();
}

Deck::Deck(std::vector<Card> cards)
{
    deck = cards;
    deckSize = deck.size();
    deckiter = deck.begin();
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
    deckSize--;
    if (deckiter != deck.end())
    {
        Card temp = *deckiter;
        deckiter++;
        return temp;
    }
}

Card Deck::fakeDeal()
{
    if (deckiter != deck.end())
        return *deckiter;
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
    deckiter = deck.begin();
}

void Deck::empty()
{
    deckSize = 0;
}