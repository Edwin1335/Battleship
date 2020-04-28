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

    Ship *ships;
    void Create_Ships();
    bool Ships_Overlap(int, int, int, int, int);
    int Convert_Char_to_Int(char);
    void Place_Ships(int, int, int, int, int);

public:
    ShipBoard();
    Ship *getShips();
    bool Ship_Placement_is_Possible(std::string, std::string, int);
};

ShipBoard::ShipBoard()
{
    ships = new Ship[7];
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

ShipBoard::Ship *ShipBoard::getShips()
{
    return ships;
}

bool ShipBoard::Ship_Placement_is_Possible(std::string firstCoor, std::string secCoor, int shipNum)
{
    int rowOne, rowTwo, colOne, colTwo;
    int size = ships[shipNum].size;
    std::string parseString;

    // Convert the string values to appropriate integers.
    colOne = Convert_Char_to_Int(firstCoor[0]);
    colTwo = Convert_Char_to_Int(secCoor[0]);
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
    if (Ships_Overlap(colOne - 1, rowOne - 1, colTwo - 1, rowTwo - 1, shipNum))
    {
        return false;
    }

    // If allowed begin to place the ship.
    Place_Ships(colOne - 1, rowOne - 1, colTwo - 1, rowTwo - 1, shipNum);

    return true;
}

int ShipBoard::Convert_Char_to_Int(char c)
{
    if (c == 'A' || c == 'a')
    {
        return 1;
    }
    else if (c == 'B' || c == 'b')
    {
        return 2;
    }
    else if (c == 'C' || c == 'c')
    {
        return 3;
    }
    else if (c == 'D' || c == 'd')
    {
        return 4;
    }
    else if (c == 'E' || c == 'e')
    {
        return 5;
    }
    else if (c == 'F' || c == 'f')
    {
        return 6;
    }
    else if (c == 'G' || c == 'g')
    {
        return 7;
    }
    else if (c == 'H' || c == 'h')
    {
        return 8;
    }
    else if (c == 'I' || c == 'i')
    {
        return 9;
    }
    else if (c == 'J' || c == 'j')
    {
        return 10;
    }
    else
    {
        return -1;
    }
}

bool ShipBoard::Ships_Overlap(int c1, int r1, int c2, int r2, int shipNum)
{
    Node *temp = TRCorner;
    // Find location for Column1 and Row1.
    while (temp->column != c1)
    {
        temp = temp->right;
    }
    while (temp->row != r1)
    {
        temp = temp->bottom;
    }

    // Begin checking fro overlapping
    // Temp is now at the front of the ship.
    if (temp->occupied == true)
    {
        std::cout << "ERROR: Front of ship cannot overlap." << std::endl;
        return true;
    }

    while (temp->column != c2)
    {
        // Check of to move right or left.
        if (c1 <= c2)
        {
            temp = temp->right;
        }
        else
        {
            temp = temp->left;
        }
        if (temp->occupied == true)
        {
            std::cout << temp->column << "  " << temp->row << std::endl;
            std::cout << "ERROR: Ships cannot overlap." << std::endl;
            return true;
        }
    }

    // Move to the correcct row.
    while (temp->row != r2)
    {
        if (r1 <= r2)
        {
            temp = temp->bottom;
        }
        else
        {
            temp = temp->top;
        }
        if (temp->occupied == true)
        {
            std::cout << temp->column << "  " << temp->row << std::endl;
            std::cout << "ERROR: Ships cannot overlap." << std::endl;
            return true;
        }
    }

    return false;
}

void ShipBoard::Place_Ships(int c1, int r1, int c2, int r2, int ship)
{
    Node *temp = TRCorner;
    Node *temp2;
    Node *current;

    // Find location for Column1 and Row1.
    while (temp->column != c1)
    {
        temp = temp->right;
    }
    while (temp->row != r1)
    {
        temp = temp->bottom;
    }

    // This ship's front poinyer will be equal to temp.
    ships[ship].shipFront = temp;
    ships[ship].shipFront->value = ships[ship].Initials;
    ships[ship].shipFront->occupied = true;

    // new Temp2 to contiue the search for Column2 and Row2.
    temp2 = ships[ship].shipFront;
    current = temp2;

    // Move to the correct column.
    while (temp2->column != c2)
    {
        // Check of to move right or left.
        if (c1 <= c2)
        {
            temp2 = temp2->right;
        }
        else
        {
            temp2 = temp2->left;
        }
        temp2->occupied = true;
        temp2->value = ships[ship].Initials;
        current->next = temp2;
        current = current->next;
    }

    // Move to the correcct row.
    while (temp2->row != r2)
    {
        if (r1 <= r2)
        {
            temp2 = temp2->bottom;
        }
        else
        {
            temp2 = temp2->top;
        }
        temp2->occupied = true;
        temp2->value = ships[ship].Initials;
        current->next = temp2;
        current = current->next;
    }

    if (current != NULL)
    {
        current->next = NULL;
    }

    // Save some merory space.
    current = NULL;
    temp = NULL;
    temp2 = NULL;
    delete temp2;
    delete current;
    delete temp;
}
