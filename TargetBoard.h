#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include "Board.h"

class TargetBoard : public Board
{
public:
    std::string hit;
    void Update_Board();
    
public:
    TargetBoard();
    void Player_Guess(int, int, int, int);
};

TargetBoard::TargetBoard()
{
    hit = " HIT ";
    this->Create_Nodes();
}