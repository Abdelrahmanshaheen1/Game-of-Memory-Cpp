#pragma once
#include"Card.h"
#ifndef DECK_H
#define DECK_H
#include <iostream>
#define row 4
#define col 4

class Deck
{

private:
    
    Card* cards[row][col];

public:
    Deck();
    ~Deck();

    void shuffle();
    void displayGrid() ;
    void removeCard(int x, int y);
    Card* getCard(int x, int y);
    bool isAllMatched();
};


#endif 
