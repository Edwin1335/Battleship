#pragma once
#include <iostream>
#include <iomanip>
#include <string>

class Board
{
protected:
    // The values in the grid
    struct Node
    {
        int column;
        int row;
        bool occupied = false;
        bool guessed = false;
        std::string value = "     ";
        Node *left = NULL;
        Node *right = NULL;
        Node *top = NULL;
        Node *bottom = NULL;
        Node *next = NULL;
    };

    // Pointer to the Top Right hand Corner node.
    Node *TRCorner;
    Board();
    void Create_Ships();
    void Create_Nodes();
    void Print_Occupied_Spaces();

public:
    void Build_Board();
};

/*********************************************************************************
  This is the default constructor for the board funtion. There is no need for an
  ovelaoded one, because this class will be inherited by the two component classes,
  the ShipBpard and the Target Board. The constructor sets the Top Corner pointer 
  to NULL.
 *********************************************************************************/
Board::Board()
{
    TRCorner = NULL;
}

/*********************************************************************************
  The Create_Nodes uses to loops (nested) to simulate looping through a grid and 
  connect all the nodes together like in a 2d matrix. The nodes on the side, top, 
  and bottom will point to NULL. The other pointer values in the Node struct will
  point to their correspondind neighbor. 
 *********************************************************************************/
void Board::Create_Nodes()
{
    Node *temp = new Node;
    Node *ARow = NULL;
    Node *topTemp = NULL;

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            // For each iteration we need a new node.
            Node *newNode = new Node;
            newNode->column = j;
            newNode->row = i;

            // Will Adjust based on rows.
            if (i == 0)
            {
                // Check the first row. All top must be NULL.
                // Same TRCorner as the top Corner Node.
                newNode->top = NULL;
                if (i == 0 && j == 0)
                {
                    TRCorner = newNode;
                    newNode->left = NULL;
                    ARow = newNode;
                    topTemp = newNode;
                    temp = newNode;
                }
                else if (i == 0 && j != 9)
                {
                    newNode->left = temp;
                    newNode->left->right = newNode;
                    temp = newNode;
                }
                else if (i == 0 && j == 9)
                {
                    newNode->left = temp;
                    newNode->left->right = newNode;
                    newNode->right = NULL;
                }
            }
            else if (i != 9)
            {
                // All the values in the middle from row 8 - 9.
                // All top and bottom balues must be adjusted.
                if (i != 9 && j == 0)
                {
                    newNode->left = NULL;
                    ARow = topTemp;
                    newNode->top = ARow;
                    newNode->top->bottom = newNode;
                    topTemp = newNode;
                    ARow = ARow->right;
                    temp = newNode;
                }
                else if (i != 9 && j != 9)
                {
                    newNode->left = temp;
                    newNode->left->right = newNode;
                    newNode->top = ARow;
                    newNode->top->bottom = newNode;
                    ARow = ARow->right;
                    temp = newNode;
                }
                else if (i != 9 && j == 9)
                {
                    newNode->left = temp;
                    newNode->top = ARow;
                    newNode->right = NULL;
                    newNode->top->bottom = newNode;
                    newNode->left->right = newNode;
                }
            }
            else if (i == 9)
            {
                // Bottom row, all bottom vlues must point NULL to bottom.
                newNode->bottom = NULL;
                if (i == 9 && j == 0)
                {
                    ARow = topTemp;
                    topTemp = NULL;
                    newNode->left = NULL;
                    newNode->top = ARow;
                    ARow = ARow->right;
                    newNode->top->bottom = newNode;
                    temp = newNode;
                }
                else if (i == 9 && j != 9)
                {
                    newNode->left = temp;
                    newNode->left->right = newNode;
                    newNode->top = ARow;
                    newNode->top->bottom = newNode;
                    ARow = ARow->right;
                    temp = newNode;
                }
                else
                {
                    newNode->left = temp;
                    newNode->left->right = newNode;
                    newNode->top = ARow;
                    newNode->top->bottom = newNode;
                    newNode->right = NULL;
                    temp = NULL;
                    ARow = NULL;
                }
            }
        }
    }

    // Save space by deleting pointers no longer needed.
    delete ARow;
    delete temp;
    delete topTemp;
}

/*********************************************************************************
  This function will be used to help the developer(me), to find make sure that all
  the sapces marked as occupied by ships are marked correctly. It will loop thorugh
  the entire grid and change thevalues to "O" if the places is occupied.  
 *********************************************************************************/
void Board::Print_Occupied_Spaces()
{
    Node *temp = TRCorner;
    int counter = 0;

    while (temp != NULL)
    {
        for (int i = 0; i < 10; i++)
        {
            if (temp->occupied)
            {
                temp->value = "  O  ";
            }
            if (i == 9)
            {
                temp = temp->bottom;
            }
            else
            {
                if (counter % 2 == 0)
                {
                    temp = temp->right;
                }
                else
                {
                    temp = temp->left;
                }
            }
        }
        counter++;
    }
}
/*********************************************************************************
  Finally we have the Build_Board Funton the will create the bard on call with the 
  updated values of each node in each square of the grid. When the ships are placed
  on the grid, the intials will be displayed on the correspinding square. 
 *********************************************************************************/
void Board::Build_Board()
{
    Node *temp = new Node;
    temp = TRCorner;
    Node *Corner = temp;

    std::cout << " _________________________________________________________________" << std::endl;
    std::cout << "| BAT |     |     |     |     |     |     |     |     |     |     |" << std::endl;
    std::cout << "| SHP |  A  |  B  |  C  |  D  |  E  |  F  |  G  |  H  |  I  |  J  |" << std::endl;
    std::cout << "|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|" << std::endl;

    for (int i = 0; i < 10; i++)
    {
        std::cout << "|     |     |     |     |     |     |     |     |     |     |     |" << std::endl;
        std::cout << "|  " << i << "  |" << temp->value;
        temp = temp->right;
        std::cout << "|" << temp->value;
        temp = temp->right;
        std::cout << "|" << temp->value;
        temp = temp->right;
        std::cout << "|" << temp->value;
        temp = temp->right;
        std::cout << "|" << temp->value;
        temp = temp->right;
        std::cout << "|" << temp->value;
        temp = temp->right;
        std::cout << "|" << temp->value;
        temp = temp->right;
        std::cout << "|" << temp->value;
        temp = temp->right;
        std::cout << "|" << temp->value;
        temp = temp->right;
        std::cout << "|" << temp->value;
        std::cout << "|" << std::endl;
        std::cout << "|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|" << std::endl;
        Corner = Corner->bottom;
        temp = Corner;
    }
}