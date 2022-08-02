#include "Deck.h"
#include "Card.h"
#include "Main.h"

void App::resetFile(std::string fileName)
{
    std::ofstream file;
    file.open(fileName, std::ios_base::trunc);
    file.close();
}

void App::ComputeHands(std::string fileName, Deck deck, int start, int end, int *handcount)
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
                            hands.push_back(hand);
                            hand.clear();
                            counter = 0;
                            for (int a = 0; a < hands.at(hands.size() -1).size(); a++)
                            {
                                std::cout << hands.at(hands.size() -1).at(a).getCard() << std::endl;
                            }
                            std::cout << "\n";
                            *handcount++;
                        }
                    }
                }
            }
        }
        while(hands.at(0).size() > 6)
        {
            hands.at(0).front() = hands.at(0).back();
            hands.at(0).pop_back();
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
    std::cout << deck.getDeck().size() << std::endl;

    App::resetFile("handoutput1.txt");
    App::resetFile("handoutput2.txt");
    App::resetFile("handoutput3.txt");
    App::resetFile("handoutput4.txt");

    int *count1 = new int;
    int *count2 = new int;
    int *count3 = new int;
    int *count4 = new int;

    std::thread compute1(App::ComputeHands, "handoutput1.txt", deck, 0, 13, count1);
    std::thread compute2(App::ComputeHands, "handoutput2.txt", deck, 14, 27, count2);
    std::thread compute3(App::ComputeHands, "handoutput3.txt", deck, 28, 41, count3);
    std::thread compute4(App::ComputeHands, "handoutput4.txt", deck, 42, 52, count4);

    compute1.join();
    compute2.join();
    compute3.join();
    compute4.join();

    int totalHands = *count1 + *count2 + *count3 + *count4;
    delete count1;
    delete count2;
    delete count3;
    delete count4;

    std::cout << "success" << std::endl;
    std::cout << totalHands << " amount of hands" << std::endl;

    return 0;
}