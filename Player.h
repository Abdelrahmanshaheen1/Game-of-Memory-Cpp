#pragma once

#include "Player.h"
#include "PenaltyCard.h"
#include <string>
#include<iostream>
#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <string>
class Player
{

private:
    string name;
    int score;

public:
    Player();

    Player(string name);
    ~Player();

    void setName(string name);
    string getName();

    void setScore(int score);
    int getScore() ;

    void increaseScore(int points);
    void decreaseScore(int points);

    void displayScore();

};
#endif