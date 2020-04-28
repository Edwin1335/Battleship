#pragma once
#include <iostream>
#include <iomanip>
#include <string>

class TargetBoard
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
}