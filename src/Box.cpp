#include "Box.hpp"

Boxx::cleanTerminal(){
#ifdef _WIN32
    system("cls"); // Windows
#else
    system("clear"); // Linux/Mac
#endif    
}

Box::Box(){}

Box::playBox(){
    int answer = -1;
    while(answer != 2){
        this->cleanTerminal();
        cout << "Bienvenue dans la boite de révision\n";
        cout << "1 . Ajouter une carte\n";
        cout << "2 . Commencer\n";
        cout << "3 . Quitter\n";
        cin >> answer;
        if(cin.fail()){
            cin.clear();
            cin.ignore();
        }
        if(answer == 1){
            this->addUserCard();
        }else if(answer == 3){
            return;
        }

    }
    this->researchPlayablesCards();
    this->shuffle();

    for(int i = 0; i < this->cards.size(); i++){
        this->playCard(this->cards[i]);
    }
    this->finish();
}

Box::shuffle(){
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(this->cards.begin(), this->cards.end(), g);
}

Box::addUserCard(){
    string question;
    string answer1;
    string answer2;

    std::cout << "Enter la question: \n";
    std::cin >> question;
    std::cout << "Enter la réponce 1: \n";
    std::cin >> answer1;
    std::cout << "Enter la réponce 2: \n";
    std::cin >> answer2;

    this->makeCard(question, answer1, answer2, 0);
}

Box::researchPlayablesCards(){
    //todo research cardsfile
}

Box::makeCard(string question, string answer1, string answer2, short level){
    Card card(question, answer1, answer2, level);
    this->cards.push_back(card);
}

Box::int playCard(Card card){
    bool noGoodAnswer = true;
    int answer = -1;
    while (answer < 1 && answer > 2){
        this->cleanTerminal();
        cout << "1. je connais\n"
        cout << "2. je ne connais pas\n\n"
        cout << "7. voir les réponces\n";
        cout << "0. Quiter\n";
        cout << card.getQuestion() << "\n\n";
        if(ansewer == 7){
            cout << card.getAnswer1() << "\n";
            cout << card.getAnswer2() << "\n";
        }
        cin >> answer;
        if(cin.fail()){
            cin.clear();
            cin.ignore();
            continue;
        }
        switch (answer){
            case 0:
                return -1;
            case 1:
                goodCards.push_back(card);
                break;
            case 2:
                badCards.push_back(card);
                break;
            default:
                break;
        }
    }
    return 0;
}

Box::finish(){
    this->cleanTerminal();
    cout << "Fin de la révision\n";
    cout << "Vous avez répondu correctement à " << this->goodCards.size() << " cartes\n";
    cout << "Vous avez répondu incorrectement à " << this->badCards.size() << " cartes\n";
    int remainingCardsIndexStart = this->goodCards.size() + this->badCards.size();
    //todo write file
}