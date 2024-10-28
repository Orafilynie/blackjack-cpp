#include <iostream>
#include <algorithm>
#include <random>

using namespace std;

/*VARIABLES GLOBALES*/

int card[52] = {1,2,3,4,5,6,7,8,9,10,1,2,3,4,5,6,7,8,9,10,1,2,3,4,5,6,7,8,9,10,1,2,3,4,5,6,7,8,9,10,11,12,13,11,12,13,11,12,13,11,12,13};
string player[26];
string dealer[26];

string currentCardName;

int currentCardArrayPos = 0;
int playerCardArrayPos = 0;
int dealerCardArrayPos = 0;

int currentCard = 0;
int currentCardValue = 0;

int playerCardsCount = 0;
int playerCardsValue = 0;

int dealerCardsCount = 0;
int dealerCardsValue = 0;

int tokens = 50;
int balcheck = 0;
int bet = 0;

bool isPlayer = false;
bool isDealer = false;
bool isDealerVisible = false;

/*DÉCLARATIONS ANTICIPÉES*/

void initMenu();
void initBet();

/*FONCTIONS DU CODE*/

void clearConsole() {
    system("chcp 65001");

    if (system("cls") != 0) {
        system("clear");
    }
}

void resetGame() {
    currentCardArrayPos = 0;
    playerCardArrayPos = 0;
    dealerCardArrayPos = 0;

    currentCard = 0;
    currentCardValue = 0;

    playerCardsCount = 0;
    playerCardsValue = 0;

    dealerCardsCount = 0;
    dealerCardsValue = 0;

    isPlayer = false;
    isDealer = false;

    currentCardName.clear();

    for (int i = 0; i <= 25; i++) {
        player[i].clear();
        dealer[i].clear();
    }

    initMenu();
}

void initCardDeck() {
    clearConsole();
    
    random_device rd;
    mt19937 g(rd());

    shuffle(begin(card), end(card), g);
}

void choosePlayerAceValue() {
    int aceactionchoice = 0;

    clearConsole();

    cout << "Vous avez trouvé un As ! Choississez sa valeur entre 1 et 11." << endl << endl;
    cout << "Choisissez la valeur : ";

    cin >> aceactionchoice;

    switch (aceactionchoice) {
        case 1:
            currentCardValue = 1;
            break;
        case 11:
            currentCardValue = 11;
            break;
        default:
            choosePlayerAceValue();
            break;
        }
}

void dealerAceValue() {
    if (dealerCardsValue <= 10) {
        currentCardValue = 11;
    } else {
        currentCardValue = 1;
    }
}

void getAceValue() {
    if (isPlayer == true) {
        choosePlayerAceValue();
    } else if (isDealer == true) {
        dealerAceValue();
    }
}

void setCurrentCardValue() {
    switch (currentCard) {
        case 1:
            getAceValue();
            break;
        case 11:
            currentCardValue = 10;
            break;
        case 12:
            currentCardValue = 10;
            break;
        case 13:
            currentCardValue = 10;
            break;
        default:
            currentCardValue = currentCard;
    }
}

void getCard() {
    currentCard = card[currentCardArrayPos];
    currentCardArrayPos++;
    setCurrentCardValue();
}

void getCardName() {

    switch (currentCard) {
        case 1:
            currentCardName = "As";
            break;
        case 11:
            currentCardName = "Valet";
            break;
        case 12:
            currentCardName = "Dame";
            break;
        case 13:
            currentCardName = "Roi";
            break;
        default:
            currentCardName = to_string(currentCard);
            break;
    }
}

void savePlayerCurrentCard() {
    getCardName();
    player[playerCardArrayPos] = currentCardName;
    playerCardsValue = playerCardsValue + currentCardValue;
    playerCardArrayPos++;
    playerCardsCount++;
}

void saveDealerCurrentCard() {
    getCardName();
    dealer[dealerCardArrayPos] = currentCardName;
    dealerCardsValue = dealerCardsValue + currentCardValue;
    dealerCardArrayPos++;
    dealerCardsCount++;
}

void displayPlayerDrawLost() {
    int lostdrawplayeractionchoice = 0;

    clearConsole();

    cout << "Vous avez perdu ! La valeur de votre main à dépassé 21." << endl << endl;

    cout << "Cartes du joueur : ";

    for (int i = 0; i < playerCardsCount; i++) {
        cout << player[i] << " ";
    }

    cout << endl;

    cout << "Valeur des cartes du joueur : " << playerCardsValue << endl << endl << endl;

    cout << "Vous avez également perdu votre mise de " << bet << " jetons." << endl << endl << endl;

    cout << "1. Menu" << endl;
    cout << "2. Quitter" << endl << endl;
    cout << "Choisissez une action : ";

    cin >> lostdrawplayeractionchoice;

    switch (lostdrawplayeractionchoice) {
        case 1:
            resetGame();
            break;
        case 2:
            exit(0);
            break;
        default:
            clearConsole();
            displayPlayerDrawLost();
            break;
    }
}

void displayPlayerGapLost() {
    int lostgapplayeractionchoice = 0;

    clearConsole();

    cout << "Vous avez perdu ! Votre main est moins proche de 21 que celle du croupier." << endl << endl << endl;

    cout << "Cartes du croupier : ";

    for (int i = 0; i < dealerCardsCount; i++) {
        cout << dealer[i] << " ";
    }

    cout << endl;

    cout << "Valeur des cartes du joueur : " << dealerCardsValue << endl << endl;

    cout << "Cartes du joueur : ";

    for (int i = 0; i < playerCardsCount; i++) {
        cout << player[i] << " ";
    }

    cout << endl;

    cout << "Valeur des cartes du joueur : " << playerCardsValue << endl << endl << endl;

    cout << "Vous avez également perdu votre mise de " << bet << " jetons." << endl << endl << endl;

    cout << "1. Menu" << endl;
    cout << "2. Quitter" << endl << endl;
    cout << "Choisissez une action : ";

    cin >> lostgapplayeractionchoice;

    switch (lostgapplayeractionchoice) {
        case 1:
            resetGame();
            break;
        case 2:
            exit(0);
            break;
        default:
            clearConsole();
            displayPlayerGapLost();
            break;
    }
}

void displayDealerDrawLost() {
    int lostdrawdealeractionchoice = 0;

    clearConsole();

    cout << "Vous avez gagné ! La valeur de la main du croupier à dépassé 21." << endl << endl;

    cout << "Cartes du croupier : ";

    for (int i = 0; i < dealerCardsCount; i++) {
        cout << dealer[i] << " ";
    }

    cout << endl;

    cout << "Valeur des cartes du croupier : " << dealerCardsValue << endl << endl << endl;

    cout << "Vous avez également gagné votre mise de " << bet << " jetons. " << "Vous remporter donc " << bet << " jetons supplémentaires." << endl << endl << endl;

    tokens = tokens + bet * 2;

    cout << "1. Menu" << endl;
    cout << "2. Quitter" << endl << endl;
    cout << "Choisissez une action : ";

    cin >> lostdrawdealeractionchoice;

    switch (lostdrawdealeractionchoice) {
        case 1:
            resetGame();
            break;
        case 2:
            exit(0);
            break;
        default:
            clearConsole();
            displayDealerDrawLost();
            break;
    }
}

void displayDealerGapLost() {
    int lostgapdealeractionchoice = 0;

    clearConsole();

    cout << "Vous avez gagné ! Votre main est plus proche de 21 que celle du croupier." << endl << endl;

    cout << "Cartes du joueur : ";

    for (int i = 0; i < playerCardsCount; i++) {
        cout << player[i] << " ";
    }

    cout << endl;

    cout << "Valeur des cartes du joueur : " << playerCardsValue << endl << endl;

    cout << "Cartes du croupier : ";

    for (int i = 0; i < dealerCardsCount; i++) {
        cout << dealer[i] << " ";
    }

    cout << endl;

    cout << "Valeur des cartes du joueur : " << dealerCardsValue << endl << endl << endl;

    cout << "Vous avez également gagné votre mise de " << bet << " jetons. " << "Vous remporter donc " << bet << " jetons supplémentaires." << endl << endl << endl;

    tokens = tokens + bet * 2;

    cout << "1. Menu" << endl;
    cout << "2. Quitter" << endl << endl;
    cout << "Choisissez une action : ";

    cin >> lostgapdealeractionchoice;

    switch (lostgapdealeractionchoice) {
        case 1:
            resetGame();
            break;
        case 2:
            exit(0);
            break;
        default:
            clearConsole();
            displayDealerDrawLost();
            break;
    }
}

void displayEquality() {
    int equalityplayeractionchoice = 0;

    clearConsole();

    cout << "Vous êtes en égalité ! Votre main est égale à celle du croupier." << endl << endl << endl;

    cout << "Cartes du croupier : ";

    for (int i = 0; i < dealerCardsCount; i++) {
        cout << dealer[i] << " ";
    }

    cout << endl;

    cout << "Valeur des cartes du joueur : " << dealerCardsValue << endl << endl;

    cout << "Cartes du joueur : ";

    for (int i = 0; i < playerCardsCount; i++) {
        cout << player[i] << " ";
    }

    cout << endl;

    cout << "Valeur des cartes du joueur : " << playerCardsValue << endl << endl << endl;

    cout << "Vous avez récuperéz votre mise de " << bet << " jetons sans gains supplémentaires." << endl << endl << endl;

    tokens = tokens + bet;

    cout << "1. Menu" << endl;
    cout << "2. Quitter" << endl << endl;
    cout << "Choisissez une action : ";

    cin >> equalityplayeractionchoice;

    switch (equalityplayeractionchoice) {
        case 1:
            resetGame();
            break;
        case 2:
            exit(0);
            break;
        default:
            clearConsole();
            displayEquality();
            break;
    }
}

void compareHands() {
    int playerGap = 0;
    int dealerGap = 0;

    playerGap = 21 - playerCardsValue;
    dealerGap = 21 - dealerCardsValue;

    if (playerGap < dealerGap) {
        displayDealerGapLost();
    } else if (playerGap == dealerGap) {
        displayEquality();
    } else {
        displayPlayerGapLost();
    }
}

void initDealer() {
    while (dealerCardsValue <= 17) {
        getCard();
        saveDealerCurrentCard();
    }
    if (dealerCardsValue <= 21) {
        compareHands();
    } else {
        displayDealerDrawLost();
    }
}

void revealDealerCard() {
    clearConsole();

    int revealactionchoice = 0;

    isPlayer = false;
    isDealer = true;

    cout << "Cartes du croupier : ";

    for (int i = 0; i < dealerCardsCount; i++) {
        cout << dealer[i] << " ";
    }

    cout << endl;
    cout << "Valeur des cartes du croupier : " << dealerCardsValue << endl << endl;

    cout << "1. Continuer" << endl << endl;
    cout << "Choisissez une action : ";
    
    cin >> revealactionchoice;

        switch (revealactionchoice) {
            case 1:
                initDealer();
                break;
            default:
                clearConsole();
                revealDealerCard();
                break;
        }
}

void displayGame() {
    clearConsole();

    if (playerCardsValue <= 21) {
        int gameactionchoice = 0;

        cout << "Carte visible du croupier : " << dealer [0] << endl << endl;

        cout << "Cartes du joueur : ";

        for (int i = 0; i < playerCardsCount; i++) {
            cout << player[i] << " ";
        }

        cout << endl << "Nombre de cartes du joueur : " << playerCardsCount << endl;
        cout << "Valeur des cartes du joueur : " << playerCardsValue << endl;

        cout << endl << endl;

        cout << "1. Piocher" << endl;
        cout << "2. Reveler" << endl << endl;
        cout << "Choisissez une action : ";
    
        cin >> gameactionchoice;

        switch (gameactionchoice) {
            case 1:
                getCard();
                savePlayerCurrentCard();
                displayGame();
                break;
            case 2:
                revealDealerCard();
                break;
            default:
                clearConsole();
                displayGame();
                break;
        }
    } else {
        displayPlayerDrawLost();
    }
}

void initGame() {
    clearConsole();

    initCardDeck();

    for (int i = 0; i <= 1; i++) {
        isPlayer = true;
        isDealer = false;

        getCard();
        savePlayerCurrentCard();
    }

    for (int i = 0; i <= 1; i++) {
        isPlayer = false;
        isDealer = true;

        getCard();
        saveDealerCurrentCard();
    }

    isPlayer = true;
    isDealer = false;

    displayGame();
}

void balanceCheck() {
    if (balcheck > tokens) {
        clearConsole();
        int betamountactionchoice = 0;

        cout << "Vous ne pouvez pas misez plus que ce que vous possedez ! Veuillez réessayez avec une mise valide." << endl << endl;

        cout << "1. Recommencer" << endl;
        cout << "2. Menu" << endl << endl;
        cout << "Choisissez une action : ";

        cin >> betamountactionchoice;

        switch (betamountactionchoice)
        {
        case 1:
            initBet();
            break;
        case 2:
            initMenu();
            break;
        default:
        balanceCheck();
            break;
        }
    } else {
        tokens = tokens - balcheck;
        bet = balcheck;
        initGame();
    }
}

void initBet() {
    clearConsole();

    cout << "Vous possédez " << tokens << " jetons. Combien voulez vous miser sur cette partie ?" << endl << endl;
    cout << "Entrez le montant de la mise : ";

    cin >> balcheck;
    balanceCheck();
}

void initMenu() {
    clearConsole();

    int menuactionchoice = 0;

    cout << R"(  ____  _            _        _            _       _____           
 |  _ \| |          | |      | |          | |     / ____|_     _   
 | |_) | | __ _  ___| | __   | | __ _  ___| | __ | |   _| |_ _| |_ 
 |  _ <| |/ _` |/ __| |/ /   | |/ _` |/ __| |/ / | |  |_   _|_   _|
 | |_) | | (_| | (__|   < |__| | (_| | (__|   <  | |____|_|   |_|  
 |____/|_|\__,_|\___|_|\_\____/ \__,_|\___|_|\_\  \_____|          
                                                                   
                                                                   
)";

    cout << endl;

    cout << "Vous possédez " << tokens << " jetons." << endl << endl;

    cout << "1. Jouer" << endl;
    cout << "2. Quitter" << endl << endl;
    cout << "Choisissez une action : ";

    cin >> menuactionchoice;

    switch (menuactionchoice) {
        case 1:
            initBet();
            break;
        case 2:
            exit(0);
            break;
        default:
            clearConsole();
            initMenu();
            break;
    }
}

/*POINT D'EXECUTION DU CODE*/

int main() {
    initMenu();
    return 0;
}