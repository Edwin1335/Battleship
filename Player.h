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
    void Convert_String_to_Coor(std::string &, int &, int &, int &, int &);

public:
    Player();
    Player(std::string);
    void Place_Ships();
    std::string Attack();
    void Defend(std::string);
    void Display_Boards();
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
    // Vlaues to retrieve from the user.
    std::string from;
    std::string to;
    bool incorrectPlacement;

    // Display to place the ships based by name and give info on ship size.
    for (int i = 0; i < 7; i++)
    {
        // Lopp incase incorrect input after CheckPissobleShiPlacemetn.
        incorrectPlacement = true;
        while (incorrectPlacement)
        {
            sBoard.Build_Board();
            std::cout << std::endl;
            std::cout << std::setw(15) << std::left << "Place ship"
                      << "\"" << (sBoard.getShips() + i)->name << "\"" << std::endl;
            std::cout << std::setw(16) << "Size: " << (sBoard.getShips() + i)->size << std::endl;
            std::cout << "Example: From: A1 To: " << (sBoard.getShips() + i)->size << " apart" << std::endl;
            std::cout << "From: ";
            std::cin >> from;
            if (i == 5 || i == 6)
            {
                to = from;
            }
            else
            {
                std::cout << "To: ";
                std::cin >> to;
            }
            if (sBoard.Ship_Placement_is_Possible(from, to, i))
            {
                incorrectPlacement = false;
            }
        }
    }
}

void Player::Defend(std::string)
{
    int col1, row1, col2, row2;
}

void Player::Convert_String_to_Coor(std::string &input, int &c1, int &r1, int &c2, int &r2)
{
    
}

void Player::Display_Boards()
{
    // Add the an extra elemenst to the print out whne printing out the board.
    std::string display = name + "'s boards";

    //
    std::cout << std::setw(display.size() * 3) << std::setfill('_') << "_" << std::setfill(' ') << std::endl;
    std::cout << "|" << std::setw(display.size() * 3 - 1) << std::setfill(' ') << "|" << std::endl;
    std::cout << "|" << std::setw(display.size() - 1) << std::setfill(' ') << " ";
    std::cout << std::setw(display.size()) << display;
    std::cout << std::setw(display.size()) << "|" << std::endl;
    std::cout << "|" << std::setw(display.size() * 3 - 1) << std::setfill('_') << "|" << std::endl;

    sBoard.Build_Board();
    tBaord.Build_Board();
}
