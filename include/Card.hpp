#ifndef CARD_HPP
#define CARD_HPP

#include <string>
using std::string;

class Card{
public:
    Card(string question, string answer, int level);
    Card(string question, string answer);
    
    string getQuestion();
    string getAnswer();
    int getLevel();
        
private:
    string question;
    string answer;
    int level;
};

#endif //CARD_HPP