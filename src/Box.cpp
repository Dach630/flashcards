#include "../include/Box.hpp"




Box::Box(){
    this->cardsFile.open(this->CARD_FILE_NAME);
    if(!this->cardsFile){
        cout << "Impossible d'ouvrir le fichier de cartes\n";
        exit(1);
    }
    this->tempFile.open(this->FILE_NAME_BEFORE_FINISH);
    if(!this->tempFile){
        cout << "Impossible d'ouvrir le fichier temp\n";
        cardsFile.close();
        exit(1);
    }
}

void Box::playBox(){
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

void Box::shuffle(){
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(this->cards.begin(), this->cards.end(), g);
}

void Box::addUserCard(){
    string question;
    string answer;

    std::cout << "Enter la question: \n";
    std::cin >> question;
    std::cout << "Enter la réponce 1: \n";
    std::cin >> answer;

    this->addCard(question, answer, 0);
}

vector<string> Box::splitInformation(string information){
    vector<string> tokens;
    size_t start = 0, end;

    while ((end = information.find(DELIMITER, start)) != string::npos) {
        tokens.push_back(information.substr(start, end - start));
        start = end + 1;
    }

    tokens.push_back(information.substr(start));

    return tokens;
}

void Box::researchPlayablesCards(){
    //cardInformation = question + DELIMITER + answer + DELIMITER + level + DELIMITER + newDateForNextRevision
    //or cardInformation = question + DELIMITER + answer + DELIMITER + level 
    string cardInformation;
    vector<string> cardsToken;
    while (std::getline(this->cardsFile, cardInformation)){
        cardsToken = this->splitInformation(cardInformation);
        if(cardsToken.size() == 3){
            this->addCard(cardsToken[0], cardsToken[1], std::stoi(cardsToken[2]));
        }else if(cardsToken.size() == 4){
            if(this->checkDate(cardsToken[3])){
                this->addCard(cardsToken[0], cardsToken[1], std::stoi(cardsToken[2]));
            }else{
                this->tempFile << cardInformation << "\n";
            }
        }
    }
}

void Box::addCard(string question, string answer, int level){
    Card card(question, answer, level);
    this->cards.push_back(card);
}

int Box::playCard(Card card){
    bool noGoodAnswer = true;
    int answer = -1;
    while (answer < 1 && answer > 2){
        this->cleanTerminal();
        cout << "1. je connais\n";
        cout << "2. je ne connais pas\n";
        cout << "7. voir les réponces\n";
        cout << "0. Quiter\n";
        cout << card.getQuestion() << "\n\n";
        if(answer == 7){
            cout << card.getAnswer() << "\n";
        }
        cin >> answer;
        if(cin.fail()){
            cin.clear();
            cin.ignore();
            continue;
        }
        switch (answer){
            case 0:
                this->finish();
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

void Box::finish(){
    this->cleanTerminal();
    cout << "Fin de la révision\n";
    cout << "Vous avez répondu correctement à " << this->goodCards.size() << " cartes\n";
    cout << "Vous avez répondu incorrectement à " << this->badCards.size() << " cartes\n";
    int remainingCardsIndexStart = this->goodCards.size() + this->badCards.size();
    
    auto today = floor<days>(system_clock::now());
    
    int newLevel;
    auto newDateForNextRevision = today;
    for(int i = 0; i < this->goodCards.size(); i++){
        newLevel = this->goodCards[i].getLevel() + 1;
        newDateForNextRevision = today + days(this->SPACE_BETWEEN_CARDS[newLevel]);
        this->tempFile 
        << this->goodCards[i].getQuestion() << this->DELIMITER 
        << this->goodCards[i].getAnswer() << this->DELIMITER 
        << newLevel << this->DELIMITER 
        << "date"<< "\n"; //todo
    }
    newDateForNextRevision = today + days(1);
    for(int i = 0; i < this->badCards.size(); i++){
        this->tempFile 
        << this->badCards[i].getQuestion() << this->DELIMITER 
        << this->badCards[i].getAnswer() << this->DELIMITER 
        << 0 << this->DELIMITER 
        << "newDateForNextRevision" << "\n";
    }
    for(int i = remainingCardsIndexStart; i < this->cards.size(); i++){
        newLevel = this->cards[i].getLevel() - 1;
        this->tempFile 
        << this->cards[i].getQuestion() << this->DELIMITER 
        << this->cards[i].getAnswer() << this->DELIMITER 
        << newLevel << "\n";
    }
    
    this->closeFiles();
    
    if(std::filesystem::remove(CARD_FILE_NAME) != 0){
        cout << "Impossible de supprimer le fichier cards\n";
    }
    try {
        std::filesystem::rename(FILE_NAME_BEFORE_FINISH, CARD_FILE_NAME);
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Erreur : " << e.what() << std::endl;
    }
    exit(0);
}

void Box::closeFiles(){
    this->cardsFile.close();
    this->tempFile.close();
}

bool Box::checkDate(string information){
    /*
    std::tm tm = {};
    std::istringstream ss(information);
    ss >> std::get_time(&tm, "%Y-%m-%d"); 

    std::time_t today_t = std::chrono::system_clock::to_time_t(today);
    std::tm today_tm = *std::localtime(&today_t);

    return std::mktime(const_cast<std::tm*>(&date)) < std::mktime(&today_tm);

    auto today = floor<days>(system_clock::now());
    */
    return false;
}


void Box::cleanTerminal(){
    #ifdef _WIN32
        system("cls"); // Windows
    #else
        system("clear"); // Linux/Mac
    #endif    
}