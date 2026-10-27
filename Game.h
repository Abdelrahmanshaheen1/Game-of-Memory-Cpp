#pragma once
#include "Card.h"

#include <string>
#include<iostream>
#ifndef GAME_H
#define GAME_H
#include "Player.h"
#include "Deck.h"
#include <iostream>
class Game
{
private:
    Player player1;
    Player player2;
    Deck deck;
    bool turn;
public:
    Game(string name1, string name2);
    ~Game();
    void handleTurn(Player& currentPlayer);
    void switchTurn();
    //void initializeGame();
    void start(); 

};
#endif