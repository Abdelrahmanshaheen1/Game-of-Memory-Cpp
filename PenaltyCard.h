#pragma once
#include "Card.h"
#include "Player.h"
#include <string>
#include<iostream>
#ifndef PENALTYCARD_H
#define PENALTYCARD_H

#include <iostream>
using namespace std;

class PenaltyCard : public Card {
public:
    PenaltyCard(int number);
    ~PenaltyCard();
    void display();
};


#endif
