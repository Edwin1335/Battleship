#pragma once
#include <iostream>
#include <string>
#include "Board.h"

class ShipBoard : public Board
{
private:
    // The ships for the grid
    struct Ship
    {
        std::string name;
        std::string Initials;
        int size;
        int intact;
        bool destroyed;
        Node *shipFront;
    };

    Ship ships[7];
    void Create_Ships();
    bool Possible_Ship_Placement(std::string, std::string, int);
    void Begin_Place_Ships(int, int, int, int, int);

public:
    ShipBoard();
    void Place_Ships();
};

ShipBoard::ShipBoard()
{
    this->Create_Ships();
    this->Create_Nodes();
}

/*********************************************************************************
  The Create _Ships() class creates the 7 ships that will be sued in our game. The
  function initializes all their attributes that will be needed to keep track of 
  the occurrences in the game. Such as Their name, size and Initals to be marked
  on the grid/map.
 *********************************************************************************/
void ShipBoard::Create_Ships()
{
    // Aricraft Ship
    ships[0].destroyed = false;
    ships[0].Initials = "  A  ";
    ships[0].name = "Aircraft Carrier";
    ships[0].shipFront = NULL;
    ships[0].size = 5;

    // Battleship Ship
    ships[1].destroyed = false;
    ships[1].Initials = "  B  ";
    ships[1].name = "Battleship";
    ships[1].shipFront = NULL;
    ships[1].size = 4;

    // Cruiser Ship
    ships[2].destroyed = false;
    ships[2].Initials = "  C  ";
    ships[2].name = "Cruiser";
    ships[2].shipFront = NULL;
    ships[2].size = 5;

    // Destroyers Ships
    for (int i = 3; i < 5; i++)
    {
        ships[i].destroyed = false;
        ships[i].Initials = "  D  ";
        ships[i].name = "Destroyer";
        ships[i].shipFront = NULL;
        ships[i].size = 2;
    }

    // Submarines Ships
    for (int i = 5; i < 7; i++)
    {
        ships[i].destroyed = false;
        ships[i].Initials = "  S  ";
        ships[i].name = "Submarines";
        ships[i].shipFront = NULL;
        ships[i].size = 1;
    }
}

void ShipBoard::Place_Ships()
{
    // Values to be retrieved by the user.
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
            Build_Board();
            std::cout << std::endl;
            std::cout << std::setw(15) << std::left << "Place ship"
                      << "\"" << ships[i].name << "\"" << std::endl;
            std::cout << std::setw(16) << "Size: " << ships[i].size << std::endl;
            std::cout << "Example: From: A1 To: " << ships[i].size << " apart" << std::endl;
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
            if (Possible_Ship_Placement(from, to, i))
            {
                incorrectPlacement = false;
            }
        }
    }
}

bool ShipBoard::Possible_Ship_Placement(std::string colOne, std::string rowOne, int shipNum)
{
    int rowOne, rowTwo, colOne, colTwo;
    int size = ships[shipNum].size;
    std::string parseString;

    // Convert the string values to appropriate integers.
    colOne = convertChartoInt(firstCoor[0]);
    colTwo = convertChartoInt(secCoor[0]);
    parseString = firstCoor.substr(1, firstCoor.find(' '));
    try
    {
        rowOne = std::stoi(parseString);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        std::cout << "ERROR: Incorrect input format" << std::endl;
        return false;
    }
    parseString = secCoor.substr(1, secCoor.find(' '));
    try
    {
        rowTwo = std::stoi(parseString);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        std::cout << "ERROR: Incorrect input format" << std::endl;
        return false;
    }

    // Check al possible errors
    if (colOne > 10 || colTwo > 10 || colTwo <= 0 || colOne <= 0)
    {
        std::cout << "ERROR: First Value must be between 'A' to 'J'" << std::endl;
        return false;
    }
    else if (rowOne > 10 || rowTwo > 10 || rowTwo <= 0 || rowOne <= 0)
    {
        std::cout << "ERROR: Second value must be between '1' to '10'" << std::endl;
        return false;
    }
    else if (colOne != colTwo && rowOne != rowTwo)
    {
        std::cout << "Cannot place ships diagonally" << std::endl;
        return false;
    }
    else if (colTwo == colOne && (abs(rowTwo - rowOne) != size - 1))
    {
        std::cout << "ERROR: Must be " << size << " spaces apart\n";
        return false;
    }
    else if (rowOne == rowTwo && (abs(colOne - colTwo) != size - 1))
    {
        std::cout << "ERROR: Must be " << size << " spaces apart\n";
        return false;
    }

    //Check ovelapping ships
    if (shipsOverLap(colOne - 1, rowOne - 1, colTwo - 1, rowTwo - 1, shipNum))
    {
        return false;
    }

    // If allowed begin to place the ship.
    privatePlaceShip(colOne - 1, rowOne - 1, colTwo - 1, rowTwo - 1, shipNum);

    return true;
}