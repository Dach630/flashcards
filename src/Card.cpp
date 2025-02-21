#include "../include/Card.hpp"

Card::Card(string question, string answer, int level)
    : question(question), answer(answer), level((level < 0) ? 0 : (level > 11 ? 11 : level)) {}  // ✅ Initialisation en liste

/*
Card::Card(string question, string answer, int level){
    this->question = question;
    this->answer = answer;
    if(level < 0){
        this->level = 0;
    }else if (level > 11){
        this->level = 11;
    }else{
        this->level = level;
    }
}
*/
Card::Card(string question, string answer) : Card(question, answer, 0){}

string Card::getQuestion(){
    return this->question;
}

string Card::getAnswer(){
    return this->answer;
}

int Card::getLevel(){
    return this->level;
}
