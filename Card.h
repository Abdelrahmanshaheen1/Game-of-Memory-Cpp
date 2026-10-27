#pragma once
#include "Card.h"
#include <string>
#include<iostream>
#ifndef CARD_H
#define CARD_H
#include <iostream>
class Card{
   private:
        int number;
        bool faceUp;

    public:
        Card(int number);
        virtual ~Card();
        void setFaceUp(bool faceUp);
        bool isFaceUp() ;
        int getNumber() ;
        void reveal();
        void hide();
        virtual void display() ;
    };
#endif

