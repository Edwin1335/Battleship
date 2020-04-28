#pragma once
#include <iostream>
#include <string>
#include "Board.h"
#include "ShipBoard.h"
#include "TargetBoard.h"

class Player
{
private:
    ShipBoard sBoard;
    TargetBoard tBaord;
    std::string name;

public:
    Player();
    Player(std::string);
    void Place_Ships();
    std::string Attack();
    void Defend(std::string);
};

Player::Player()
{
    std::cout << "Please eneter your name: " << std::endl;
    getline(std::cin, name);
    std::cout << "Welcome  " << name << std::endl;
}

Player::Player(std::string name)
{
    this->name = name;
    std::cout << "Welcome  " << name << std::endl;
}

void Player::Place_Ships()
{
    
}

