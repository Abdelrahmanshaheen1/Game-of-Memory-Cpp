#include "Card.h"
#include "StandardCard.h"
#include "BonusCard.h"
#include "Deck.h"
#include "Game.h"
#include "Player.h"
#include "PenaltyCard.h"
#include <string>
#include<iostream>



Card::Card(int number) {
    this->number = number;
    faceUp = false;
}
Card::~Card() {}
void Card::setFaceUp(bool faceUp) { 
    this->faceUp = faceUp; 
}
bool Card::isFaceUp()  {
    return faceUp;
}
int Card::getNumber()  { 
    return number;
}
void Card::reveal() {
    faceUp = true; 
}
void Card::  hide() {
    faceUp = false;
}

void Card::display()  {
}


StandardCard::StandardCard(int number) : Card(number) {}
StandardCard::~StandardCard() {}
void StandardCard::display()  {
    if (StandardCard::isFaceUp())
        cout << StandardCard::getNumber();
    else { cout << "*"; 
    }
}

BonusCard::BonusCard(int number) : Card(number) {}
BonusCard::~BonusCard() {}
void BonusCard::display() {
    if (BonusCard::isFaceUp())
        cout << "B";
    else {
        cout << "*";
    }
    }

PenaltyCard::PenaltyCard(int number) : Card(number) {}
PenaltyCard::~PenaltyCard() {}
void PenaltyCard::display() {
    if (PenaltyCard::isFaceUp())
        cout << "p";
    else {
        cout << "*";
    }
}




Deck::Deck() {

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            cards[i][j] = nullptr;
        }
    }
    
    int cardNumber = 1;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if ((i * row + j) % 2 == 0) {
                if (cardNumber == 7) {
                    cards[i][j] = new BonusCard(cardNumber);
                }
                else if (cardNumber == 8) {
                    cards[i][j] = new PenaltyCard(cardNumber);
                }
                else {
                    cards[i][j] = new StandardCard(cardNumber);
                }
            }
            else {
                if (cardNumber ==7) {
                    cards[i][j] = new BonusCard(cardNumber++);
                }
                else if (cardNumber == 8) {
                    cards[i][j] = new PenaltyCard(cardNumber++);
                }
                else {
                    cards[i][j] = new StandardCard(cardNumber++);
                }
            }
               
            }
        }

    } 
   



Deck::~Deck() {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            delete cards[i][j];
        }
    }
}

void Deck::shuffle() {
    srand(static_cast<unsigned>(time(0)));
    for (int i = 0; i < row * col; i++) {
        int row1 = rand() % row;
        int col1 = rand() % col;
        int row2 = rand() % row;
        int col2 = rand() % col;

        swap(cards[row1][col1], cards[row2][col2]);
    }
}

void Deck::displayGrid() {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            cards[i][j]->display();
            cout << " ";
        }
        cout << endl;
    }
}

void Deck::removeCard(int x, int y) {
    cards[x][y]->reveal();

}

Card* Deck:: getCard(int x, int y) {
    return cards[x][y];
}

bool Deck::isAllMatched() {
   
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (!cards[i][j]->isFaceUp()) {
                return false;
            }
        }
    }
    return true;
}


Player::Player() {
    score = 0;
}

Player::Player(string name) {
this->name = name;
   score = 0;
}
 Player::~Player() {}

void Player::setName(string name) { 
    this->name = name; 
}
string Player::getName() {
    return name;
}
void Player::setScore(int score) {
    this->score = score; 
}
int Player::getScore() {
    return score ;


}
void Player::increaseScore(int points) {
    score += points; 
}

void Player::decreaseScore(int points) {
    score -= points; 
}


void Player::displayScore() {
    cout << name << "'s Score: " << score << endl;
}





Game::Game(string name1, string name2) : player1(name1), player2(name2), turn(true) {
    deck.shuffle();
    deck.displayGrid();
}


Game::~Game() {
}
void Game:: handleTurn(Player& currentPlayer) {
    int x1, y1, x2, y2;
    cout << currentPlayer.getName() << ", it's your turn!" << endl;
    cout << "Enter coordinates for first card (x y): "<<endl;
    cin >> x1 >> y1;
    while(x1>3||y1 > 3||x1<0||y1 < 0){
        cout << "out of range"<<endl;
        cout << "Enter coordinates for first card (x y) again: "<<endl;
        cin >> x1 >> y1;
    }
    while (deck.getCard(x1, y1)->isFaceUp()) {
        cout << "already flipped" << endl;
        cout << "Enter coordinates for first card (x y) again: " << endl;
        cin >> x1 >> y1;
    }

    Card* card1 = deck.getCard(x1, y1);
    card1->reveal();
    deck.displayGrid();

    cout << "Enter coordinates for second card (x y): "<<endl;
    cin >> x2 >> y2;
    while ( x2 > 3 || y2 > 3 ||x2 < 0 || y2 < 0) {
        cout << "out of range" << endl;
        cout << "Enter coordinates for first card (x y) again: " << endl;
        cin >> x2 >> y2;
    }
    while (deck.getCard(x2, y2)->isFaceUp()) {
        cout << "already flipped"<<endl;
        cout << "Enter coordinates for first card (x y) again: " << endl;
        cin >> x2 >> y2;
    }

    Card* card2 = deck.getCard(x2, y2);
    card2->reveal();
    deck.displayGrid();





    if (card1->getNumber() == card2->getNumber()) {   
            cout << "Match found!" << endl;
            if (card1->getNumber() == 7) {
                int n = 0;
                cout << "1: +2 points" << endl;
                cout << "2: gain +1 point and take another turn" << endl;
                cin >> n;
                while (n > 2 || n < 1) {
                    cout << "invalid number choose from 1,2" << endl;
                    cin >> n;
                }
                if (n == 1) {
                    currentPlayer.increaseScore(2);  
                    switchTurn();
                }
                else {

                    currentPlayer.increaseScore(1);
                    
                }
              
            }
            else {
                if (card1->getNumber() == 8) {
                    int n = 0;
                    cout << "1: Lose 2 points" << endl;
                    cout << "2: Lose 1 point and skip the next turn" << endl;
                    cin >> n;
                    while (n > 2 || n < 1) {
                        cout << "invalid number choose from 1,2" << endl;
                        cin >> n;
                    }
                    if (n == 1) {
                        currentPlayer.decreaseScore(2);
                        switchTurn();
                    }
                    else {
                        currentPlayer.decreaseScore(1);
                        switchTurn();
                        bool m = turn;
                        if (!deck.isAllMatched()) {
                            if (turn) {
                                handleTurn(player1);
                            }
                            else {
                                handleTurn(player2);
                            }
                        }
                       if (turn != m) {
                            switchTurn();
                        }
                    }

                }
                else {
                    currentPlayer.increaseScore(1);
                }



            }
       
            deck.removeCard(x1, y1);
            deck.removeCard(x2, y2);
        
    }
    else {
        cout << "No match, cards will be flipped back." << endl;
        if (card1->getNumber() == 7) {
            currentPlayer.increaseScore(1);
            card1->reveal();
        }
        if (card2->getNumber() == 7) {
            currentPlayer.increaseScore(1);
            card2->reveal();
        }
        if (card1->getNumber() == 8) {
            currentPlayer.decreaseScore(1);
            card1->reveal();
        }
        if (card2->getNumber() == 8) {
            currentPlayer.decreaseScore(1);
            card2->reveal();
        }
        if (card1->getNumber() > 0 && card1->getNumber() < 7) {
            card1->hide();
        }
        if (card2->getNumber() > 0 && card2->getNumber() < 7) {
            card2->hide();
        }
        switchTurn();
    }
 
    deck.displayGrid();
}

void Game:: switchTurn() {
    turn = !turn;  
}

void Game::start() {
    while (!deck.isAllMatched()) {
        if (turn) {
            handleTurn(player1);
        }
        else {
            handleTurn(player2);
        }
    }


    if (player1.getScore() > player2.getScore()) {
        cout << player1.getName() << " wins!" << endl;
    }
    else if (player2.getScore() > player1.getScore()) {
        cout << player2.getName() << " wins!" << endl;
    }
    else {
        cout << "It's a tie!" << endl;
    }
    int n = 0;
    cout << "if you want to play again press 1 else press 0" << endl;
    cin >> n;
    while (n > 1 || n < 0) {
        cout << "enta 3abet dakhal 0 or 1 " << endl;
        cin >> n;
    }
}

    int main() {
        string name1, name2;
        cout << "Enter Player 1's name: ";
        cin >> name1;
        cout << "Enter Player 2's name: ";
        cin >> name2;
        Game game(name1, name2);
        game.start();




        return 0;
    }