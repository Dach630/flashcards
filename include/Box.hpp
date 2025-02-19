#include <Card.hpp>
#include <vector>
#include <iostream>
#include <algorithm>
#include <random>
#include <cstdlib>

using namespace std::vector;
using namespace std::string;
using namespace std::cout;
using namespace std::cin;

class Box{
    public:
        Box();
        void playBox();
        
    private:
        vector<Card> cards;
        vector<Card> goodCards;
        vector<Card> badCards;
        int[12] SPACE_BETWEEN_CARDS = {1, 2, 4, 7, 11, 16, 22, 29, 37, 46, 56, 67};
 
        void shuffle();
        void addUserCard();
        void researchPlayablesCards();
        bool checkDate(string information);
        void makeCard(string question, string answer1, string answer2, short level);
        int playCard(Card card);
        void finish();
        void cleanTerminal;
}