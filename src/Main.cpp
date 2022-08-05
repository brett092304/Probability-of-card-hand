#include "Deck.h"
#include "Card.h"
#include "Main.h"

void App::resetFile(std::string fileName)
{
    std::ofstream file;
    file.open(fileName, std::ios_base::trunc);
    file.close();
}

void App::ComputeHands(std::vector<Deck> &decks, long *handsCounted)
{
    *handsCounted = -1;
    std::deque<std::vector<Card>> hands;
    std::vector<Card> hand;
    int countedHands = 0;
    for (int i = 0; i < decks.size(); i++)
    {
        decks.at(i).refill();
    }

    while (!decks.at(0).isEmpty())
    {
        for (int i = 1; i < decks.size(); i++)
        {
            if (decks.at(i).isEmpty())
            {
                decks.at(i).refill();
                hand.push_back(decks.at(i -1).dealCard());
            }
            if (i == decks.size() -1)
            {
                hand.push_back(decks.at(i).dealCard());
            }
        }
        hands.push_back(hand);
        hand.clear();
        countedHands++;
    }
    std::cout << countedHands << std::endl;
    *handsCounted = countedHands;
}

int main()
{
    std::vector<std::string> ranks = {"Ace", "King", "Queen", "Jack", "10", "9", "8", "7", "6", "5", "4", "3", "2"};
    std::vector<int> values = {11, 10, 10, 10, 10, 9, 8, 7, 6, 5, 4, 3, 2};
    std::vector<std::string> suits = {"Clubs", "Diamonds", "Spades", "Hearts"};

    int handSize;
    std::cout << "Hand Size: ";
    std::cin >> handSize;

    int numThreads = 5; //std::thread::hardware_concurrency();

    Deck standardDeck(ranks, suits, values);

    std::vector<std::vector<Deck>> allDecks;
    std::vector<Deck> splitDecks;
    std::vector<Deck> decks;

    int fullSize = standardDeck.getDeck().size();
    auto iter = standardDeck.getDeck().begin();
    int partsCount = numThreads;

    for (int i = 0; i < partsCount; i++)
    {
        auto partSize = fullSize / (partsCount -i);
        fullSize -= partSize;
        splitDecks.push_back(std::vector<Card>{iter, iter + partSize});
        iter += partSize;
    }

    for (int i = 0; i < splitDecks.size(); i++)
    {
        for (int j = 0; j < handSize; j++)
        {
            if (j == 0)
            {
                decks.push_back(splitDecks.at(i));
            }
            else
            {
                decks.push_back(Deck(standardDeck));
            }
        }
        allDecks.push_back(decks);
        decks.clear();
    }

    for (int i = 0; i < allDecks.size(); i++)
    {
        for (int j = 0; j < allDecks.at(0).size(); j++)
        {
            allDecks.at(i).at(j).printDeck();
            std::cout << "\n";
        }
        std::cout << "\n";
    }
    std::cout << allDecks.at(0).size() << std::endl;

    /*int timesToDump = 4;
    int whenToDump = (std::pow(allDecks.at(0).at(0).getDeck().size(), handSize)) / timesToDump;
    int timesDumped = 0;
    int counter = 0;*/

    std::vector<long*> handCounts;
    for (int i = 0; i < allDecks.size(); i++)
    {
        handCounts.emplace_back(new long);
        *handCounts.at(i) = 0;
    }

    std::vector<std::thread> thPool;
    for (int i = 0; i < allDecks.size(); i++)
    {
        thPool.push_back(std::thread(App::ComputeHands, std::ref(allDecks.at(i)), handCounts.at(i)));
    }

    std::cout << "Running another thread" << std::endl;

    for (auto &t : thPool)
    {
        t.join();
    }

    long totalHands = 0;
    for (auto &counts : handCounts)
    {
        totalHands += *counts;
    }

    for (auto &c : handCounts)
    {
        delete c;
    }

    std::cout << totalHands << " Total Hands" << std::endl;

    return 0;
}