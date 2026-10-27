#pragma once
#include "Card.h"
#include <string>
#include<iostream>
#ifndef STANDARDCARD_H
#define STANDARDCARD_H
#include <iostream>



class StandardCard : public Card {
public:
    StandardCard(int number);
    ~StandardCard();
    void display();
};


#endif