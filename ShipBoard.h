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

public:
    ShipBoard();

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

