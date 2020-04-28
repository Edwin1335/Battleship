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
            if(sBoard.Ship_Placement_is_Possible(from,to,i))
            {
                incorrectPlacement = false;
            }
        }
    }
}


