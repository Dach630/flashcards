#include <Card.hpp>

Card::Card(string question, string answer1, string answer2, int level){
    this->question = question;
    this->answer1 = answer1;
    this->answer2 = answer2;
    if(level < 0 || level >= 12){
        this->level = 0;
    }else{
        this->level = level;
    }
}

Card::Card(string question, string answer1, string answer2){
    Card::Card(question, answer1, answer2, 0);
}

Card::getQuestion(){
    return this->question;
}

Card::getAnswer1(){
    return this->answer1;
}

Card::getAnswer2(){
    return this->answer2;
}