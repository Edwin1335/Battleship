#pragma once
#include <iostream>
#include <string>
#include "Board.h"
#include "ShipBoard.h"
#include "TargetBoard.h"
/*
Testing Testing
*/
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
    // Display the Ship Board along witht the name of the board.
    std::string display = name + "'s Target Board";
    std::cout << std::setfill('_') << std::setw(display.size() * 3) <<  "_" << std::endl;
    std::cout << "|" << std::setfill(' ') << std::setw(display.size() * 3 - 1) << "|" << std::endl;
    std::cout << "|" << std::setfill(' ') << std::setw(display.size() - 1) << " ";
    std::cout << std::setw(display.size()) << display;
    std::cout << std::setw(display.size()) << "|" << std::endl;
    std::cout << "|" << std::setfill('_') << std::setw(display.size() * 3 - 1) << "|" << std::endl;
    tBaord.Build_Board();
    
    // Display the Target borad along with the name of the target board.
    display = name + "'s Ship Board";
    std::cout << std::setfill('_') << std::setw(display.size() * 3) << "_" << std::endl;
    std::cout << "|" << std::setfill(' ') << std::setw(display.size() * 3 - 1) << "|" << std::endl;
    std::cout << "|" << std::setfill(' ') << std::setw(display.size() - 1) << " ";
    std::cout << std::setw(display.size()) << display;
    std::cout << std::setw(display.size()) << "|" << std::endl;
    std::cout << "|" << std::setfill('_') << std::setw(display.size() * 3 - 1) << "|" << std::endl;
    sBoard.Build_Board();

}
