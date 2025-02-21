#ifndef BOX_HPP
#define DOX_HPP

#include "../include/Card.hpp"

#include <vector>
#include <iostream>
#include <algorithm>
#include <random>
#include <cstdlib>
#include <fstream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <filesystem>

using std::vector;
using std::string;
using std::cout;
using std::cin;
using std::ifstream;
using std::ofstream;
using std::chrono::system_clock;
using std::chrono::floor;
using std::chrono::days;

class Box{
public:
    Box();
    void playBox();
        
private:
    vector<Card> cards;
    vector<Card> goodCards;
    vector<Card> badCards;
    int SPACE_BETWEEN_CARDS[12] = {1, 2, 4, 7, 11, 16, 22, 29, 37, 46, 56, 67};
    string CARD_FILE_NAME = "data/cards";
    string FILE_NAME_BEFORE_FINISH = "data/temp";
    ifstream cardsFile;
    ofstream tempFile;
    char DELIMITER = '\t';

 
    void shuffle();
    void addUserCard();
    void researchPlayablesCards();
    bool checkDate(string information);
    void addCard(string question, string answer, int level);
    int playCard(Card card);
    void finish();
    void cleanTerminal();
    vector<string> splitInformation(string information);

    void closeFiles();
};

#endif //BOX_HPP