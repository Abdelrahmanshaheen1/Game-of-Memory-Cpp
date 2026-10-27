#pragma once
#include "Card.h"
#include <string>
#include<iostream>
#ifndef BonusCARD_H
#define BonusCARD_H
#include <iostream>
class BonusCard : public Card {

public:
    BonusCard(int number);
    ~BonusCard();
    void display() ;
};

#endif