#pragma once
#include <iostream>
#include "Player.h"

class Game
{

private:
    int Number_Players;
    void Welcome_Choose_Players();
    void Launch_One_Player_Game();
    void Launch_Two_Player_Game();

public:
    Game();
    void Launch();
};

/*********************************************************************************
  Default constuctor that will intialize the Number of players to 0. If the user
  enters the incorrect number the game will let the user try again until correct
  input is enetered. The game will have two modes(one player or two player).
**********************************************************************************/
Game::Game()
{
    Number_Players = 0;
}

/*********************************************************************************
  The only callable funiton in the main where everything comes together. First it
  will diplay the welcome screen and then it will ask the user which mode he/she 
  want to play in. One player or tow playes.
**********************************************************************************/
void Game::Launch()
{
    Welcome_Choose_Players();
    if (Number_Players == 1)
    {
        Launch_One_Player_Game();
    }
    else
    {
        Launch_Two_Player_Game();
    }
    
}

/*********************************************************************************
  The welcome screen with border for some asthetics effects. Here the user will be
  asked how many players there are and will take an input if the input is wrong, 
  the game will display and error and ask the user to try again.
**********************************************************************************/
void Game::Welcome_Choose_Players()
{
    bool correctInput = false;
    std::string userInput;

    std::cout << "___________________________" << std::endl;
    std::cout << "| Welcome to Battle Ship  |" << std::endl;
    std::cout << "|                         |" << std::endl;
    std::cout << "|    Choose number        |" << std::endl;
    std::cout << "|    Number of Players:   |" << std::endl;
    std::cout << "|       1  or  2          |" << std::endl;
    std::cout << "|_________________________|" << std::endl;

    while (correctInput == false)
    {
        std::cout << "\nPlayer: ";
        std::getline(std::cin, userInput);

        if (userInput == "1" || userInput == "2")
        {
            Number_Players = stoi(userInput);
            correctInput = true;
        }
        else
        {
            std::cout << "ERROR: Player number must be 1 or 2" << std::endl;
            std::cout << "Try again" << std::endl;
        }
    }
}

void Game::Launch_One_Player_Game()
{
    std::cout << "______________________________________" << std::endl;
    std::cout << "|                                    |" << std::endl;
    std::cout << "|      ** Player One Game **         |" << std::endl;
    std::cout << "|____________________________________|" << std::endl;

    // Begin creating first player.
    Player playerOne("Edwin");

    // Ask player to place the 7 ships 
    std::cout << "Please place the 7 ships on your board" << std::endl;
    playerOne.Place_Ships();
    playerOne.Display_Boards();
}

void Game::Launch_Two_Player_Game()
{
    std::cout << "Nothing Yet" << std::endl;
}
