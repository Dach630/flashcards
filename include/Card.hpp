#include <string>

using namespace std::string;

class Card{
public:
    Card(string question, string answer1, string answer2, short level);
    Card(string question, string answer1, string answer2);
    
    string getQuestion();
    string getAnswer1();
    string getAnswer2();
        
private:
    string question;
    string answer1;
    string answer2;
    short level;
}