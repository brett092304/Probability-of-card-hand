#include "Deck.h"
#include "Card.h"
#include "Main.h"

void App::resetFile(std::string fileName)
{
    std::ofstream file;
    file.open(fileName, std::ios_base::trunc);
    file.close();
}

void App::ComputeHands(std::vector<Deck> &decks, long *handsCounted, int fileNum)
{
    std::string filename = "output" + std::to_string(fileNum) + ".txt";
    int timesToDump = decks.at(0).getDeck().size() / 2;
    int whenToDump = ((std::pow(decks.at(0).getDeck().size(), decks.size())) / timesToDump);
    int timesDumped = 0;
    int counter = 0;

    *handsCounted = 0;
    std::deque<std::vector<Card>> hands;
    std::vector<Card> hand;
    int countedHands = 0;
    for (int i = 0; i < decks.size(); i++)
    {
        decks.at(i).refill();
    }
    int jDeck = 1;
    while (!decks.at(0).isEmpty())
    {
        bool rolledOver = false;
        for (int i = 1; i < decks.size(); i++)
        {
            if (decks.at(i).isEmpty())
            {
                decks.at(i).refill();
                hand.push_back(decks.at(i -1).dealCard());
                rolledOver= true;
            }
            if (i == decks.size() -1)
            {
                if (rolledOver)
                {
                    jDeck = 2;
                }
                for (int j = 0; j < decks.size() - jDeck; j++)
                {
                    hand.push_back(decks.at(j).fakeDeal());
                }
                hand.push_back(decks.at(i).dealCard());
                rolledOver = false;
                jDeck = 1;
            }
        }
        if (!Hand::hasDuplicates(hand))
        {
            hands.push_back(hand);
            for (int i = 0; i < hand.size(); i++)
            {
                std::cout << hand.at(i).getCard() << std::endl;
            }
            std::cout << "\n";
            countedHands++;
            counter++;
        }
        hand.clear();

        /*if (counter >= whenToDump)
        {
            std::ofstream file;
            file.open(filename, std::ios_base::app);
            for (int i = 0; i < hands.size(); i++)
            {
                for (int j = 0; j < decks.size(); j++)
                {
                    file << hands.at(i).at(j).getCard() << std::endl;
                }
                file << "\n";
            }
            file.close();
            hands.clear();
            counter = 0;
            timesDumped++;
        }*/
    }
    std::ofstream file;
    file.open(filename, std::ios_base::app);
    for (int i = 0; i < hands.size(); i++)
    {
        for (int j = 0; j < decks.size(); j++)
        {
            file << hands.at(i).at(j).getCard() << std::endl;
        }
        file << "\n";
    }
    file.close();
    hands.clear();
    std::cout << timesDumped << " Times dumped to file" << std::endl;
    *handsCounted = countedHands;
}

void App::analyzeHands(std::deque<std::vector<Card>> &hands, int start, int end, int fileNum)
{
    std::cout << hands.size() << std::endl;
    std::cout << start << "    " << end << "    " << end - start << std::endl;

    std::deque<float> timesHandAppears;
    timesHandAppears.push_back(1);
    auto handAppearedIt = timesHandAppears.end();

    for (int j = start; j < end; j++)
    {
        for (int k = 0; k < hands.size(); k++)
        {
            if (Hand::isEqual(hands.at(j), hands.at(k)))
            {
                *handAppearedIt++;
                timesHandAppears.push_back(-1);
            }
            else
            {
                timesHandAppears.push_back(1);
                handAppearedIt = timesHandAppears.end();
            }
        }
    }

    for (auto it = timesHandAppears.begin(); it < timesHandAppears.end(); it++)
    {
        *it = (*it / (float)(hands.size())) * 100;
    }

    std::ofstream outfile;
    outfile.open("finaloutput" + std::to_string(fileNum) + ".txt");
    for (int i = start; i < end; i++)
    {
        outfile << "Probability: " + std::to_string(timesHandAppears.at(i)) << std::endl;
        for (int j = 0; j < hands.at(i).size(); j++)
        {
            outfile << hands.at(i).at(j).getCard() << std::endl;
        }
        outfile << "\n";
    }
    outfile.close();
}

int main()
{
    std::vector<std::string> ranks = {"Ace", "King", "Queen", "Jack", "10", "9", "8", "7", "6", "5", "4", "3", "2"};
    std::vector<int> values = {11, 10, 10, 10, 10, 9, 8, 7, 6, 5, 4, 3, 2};
    std::vector<std::string> suits = {"Clubs", "Diamonds", "Spades", "Hearts"};

    int handSize;
    std::cout << "Hand Size: ";
    std::cin >> handSize;

    int numThreads = 6; //std::thread::hardware_concurrency();

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

    for (int i = 0; i < numThreads; i++)
    {
        App::resetFile("output" + std::to_string(i) + ".txt");
    }
    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::vector<long*> handCounts;
    for (int i = 0; i < allDecks.size(); i++)
    {
        handCounts.emplace_back(new long);
        *handCounts.at(i) = 0;
    }

    std::vector<std::thread> thPool;
    for (int i = 0; i < allDecks.size(); i++)
    {
        thPool.push_back(std::thread(App::ComputeHands, std::ref(allDecks.at(i)), handCounts.at(i), i));
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
    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::deque<std::vector<Card>> fileHands;
    auto fileHandsIter = fileHands.begin();
    std::vector<Card> fileHand;

    std::ifstream inFile;
    for (int i = 0; i < numThreads; i++)
    {
        inFile.open("output" + std::to_string(0) + ".txt");
        std::string cardStr;
        while (std::getline(inFile, cardStr))
        {
            if (cardStr.empty())
            {
                fileHands.push_back(fileHand);
                fileHand.clear();
            }
            else
            {
                std::string tempCardArray[3];
                std::stringstream ss(cardStr);
                std::string nextCard;
                int n = 0;
                while (ss >> nextCard)
                {
                    tempCardArray[n] = nextCard;
                    n++;
                }
                fileHand.push_back(Card(tempCardArray[0], tempCardArray[1], std::atoi(tempCardArray[2].c_str())));
            }
        }
        inFile.close();
    }

        for (int j = 0; j < fileHands.size(); j++)
        {
            for (int k = 0 ; k < fileHands.at(j).size(); k++)
            {
                std::cout << fileHands.at(j).at(k).getCard() << std::endl;
            }
            std::cout << "\n";
        }

        std::this_thread::sleep_for(std::chrono::seconds(2));

    std::vector<std::thread> analyzePool;
    int threadsToUse = 1;
    for (int i = numThreads; i > 0; i--)
    {
        if ((fileHands.size() % i) == 0)
        {
            threadsToUse = i;
            break;
        }
    }

    int start = 0;
    int end = start  + fileHands.size() / threadsToUse;
    int handsPerThreadSpread = fileHands.size() / threadsToUse;
    for (int i = 0; i < threadsToUse; i++)
    {
        analyzePool.emplace_back(std::thread(App::analyzeHands, std::ref(fileHands), start, end, i));
        start += handsPerThreadSpread;
        end = start + handsPerThreadSpread;
    }

    for (auto &t : analyzePool)
    {
        t.join();
    }


        /*for (int j = 0; j < fileHands.size(); j++)
        {
            for (int k = 0; k < fileHands.size(); k++)
            {
                if (Hand::isEqual(fileHands.at(j), fileHands.at(k)))
                {
                    *handAppearedIt++;
                    timesHandAppears.push_back(-1);
                }
                else
                {
                    timesHandAppears.push_back(1);
                    handAppearedIt = timesHandAppears.end();
                }
            }
        }

    for (auto it = timesHandAppears.begin(); it < timesHandAppears.end(); it++)
    {
        *it = (*it / (float)(totalHands)) * 100;
    }

    std::ofstream outfile;
    outfile.open("finaloutput.txt");
    for (int i = 0; i < fileHands.size(); i++)
    {
        outfile << "Probability: " + std::to_string(timesHandAppears.at(i)) << std::endl;
        for (int j = 0; j < fileHands.at(i).size(); j++)
        {
            outfile << fileHands.at(i).at(j).getCard() << std::endl;
        }
        outfile << "\n";
    }
    outfile.close();*/

    return 0;
}