#include "Deck.h"
#include "Card.h"
#include "Main.h"

void App::resetFile(std::string fileName)
{
    std::ofstream file;
    file.open(fileName, std::ios_base::trunc);
    file.close();
}

void App::ComputeHands(std::string fileName, Deck deck, int start, int end, long *handCount)
{
    std::deque<std::vector<Card>> hands = {};
    std::vector<Card> hand = {};

    int counter = 0;
    for (int i = 0; i < 13; i++)
    {
        hand.push_back(deck.getDeck().at(i));
        for (int j = start; j < end; j++)
        {
            hand.push_back(deck.getDeck().at(j));
            for (int k = start; k < end; k++)
            {
                hand.push_back(deck.getDeck().at(k));
                for (int n = start; n < end; n++)
                {
                    hand.push_back(deck.getDeck().at(n));
                    for (int p = start; p < end; p++)
                    {
                        hand.push_back(deck.getDeck().at(p));
                        counter++;
                        if (counter > 4)
                        {
                            while(hand.size() > 5)
                            {
                                hand.front() = hand.back();
                                hand.pop_back();
                            }
                            bool handMatches = false;
                            for (int z = 0; z < hands.size(); z++)
                            {
                                if (Hand::isEqual(hand, hands.at(z)))
                                {
                                    handMatches = true;
                                    hand.clear();
                                    counter = 0;
                                    break;
                                }
                            }
                            if (!handMatches)
                            {
                                hands.push_back(hand);
                                hand.clear();
                                counter = 0;
                                *handCount++;
                                /*for (int a = 0; a < hands.at(hands.size() -1).size(); a++)
                                {
                                    std::cout << hands.at(hands.size() -1).at(a).getCard() << std::endl;
                                }
                                std::cout << "\n";*/
                            }
                        }
                    }
                }
            }
        }
        std::ofstream file;
        file.open(fileName, std::ios_base::app);
        file << "Hands size = " << hands.size() << std::endl;
        for (int i = 0; i < hands.size(); i++)
        {
            for (int j = 0; j < hands.at(i).size(); j++)
            {
                file << hands.at(i).at(j).getCard() << std::endl;
            }
            file << "\n";
        }
        file.close();
        hands.clear();
    }
}

int main()
{
    std::vector<std::string> ranks = {"Ace", "King", "Queen", "Jack", "10", "9", "8", "7", "6", "5", "4", "3", "2"};
    std::vector<int> values = {11, 10, 10, 10, 10, 9, 8, 7, 6, 5, 4, 3, 2};
    std::vector<std::string> suits = {"Clubs", "Diamonds", "Spades", "Hearts"};

    Deck deck(ranks, suits, values);

    deck.printDeck();
    std::cout << "Current Deck" << std::endl;
    std::cout << deck.getDeck().size() << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));

    unsigned int numThreads = std::thread::hardware_concurrency();

    for (int i = 0; i < numThreads; i++)
    {
        App::resetFile("handoutput" + std::to_string(i) + ".txt");
    }

    std::cout << "generated Files" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));

    //create pointers for keeping track of number of hands
    std::vector<long*> handcounts;

    for (int i = 0; i < numThreads; i++)
    {
        handcounts.emplace_back(new long);
    }

    //generate threads to compute hands
    std::vector<std::thread> threadPool;
    threadPool.reserve(numThreads);

    int amountofCardsperThread = deck.getDeck().size() / numThreads;
    int startingPlace = 0;

    for (auto i = 0; i < numThreads; i++)
    {
        std::string filename = "handoutput" + std::to_string(i) + ".txt";
        if (i == numThreads -1)
        {
            threadPool.emplace_back(std::thread(App::ComputeHands, filename, deck, startingPlace, deck.getDeck().size(), handcounts.at(i)));
        }
        else
        {
            threadPool.emplace_back(std::thread(App::ComputeHands, filename, deck, startingPlace, startingPlace + amountofCardsperThread, handcounts.at(i)));
        }
        startingPlace += amountofCardsperThread + 1;
    }

    std::cout << "Generating Hands" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));

    for (auto &t : threadPool)
    {
        t.join();
    }

    long totalHandCount = 0;
    for (auto &count : handcounts)
    {
        totalHandCount += *count;
    }

    for (auto &count : handcounts)
    {
        delete count;
    }

    std::cout << "success" << std::endl;
    std::cout << totalHandCount << " total Hand Counts" << std::endl;
    std::cout << "Would you like to clean up temporary files (Y/n)";
    char cleanTempFiles;
    std::cin >> cleanTempFiles;
    if (cleanTempFiles != tolower('n') || cleanTempFiles == NULL)
    {
        std::system("rm *.txt");
    }

    return 0;
}