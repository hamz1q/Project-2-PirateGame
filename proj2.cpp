//Title: Project 2 for Fall 2020
//Author: Jeremy Dixon
//Date: 9/24/2020
//Description: This is main for project 2

//Include Game class
#include "Game.h"
//Include all necessary libraries
#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
using namespace std;

int main ()
{
  //Seeding thr random number Generator based of time
  srand(time(NULL));
  //Creating a new game
  Game newGame;
  newGame.StartGame();
  return 0;
}
