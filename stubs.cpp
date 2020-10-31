//Title: Project 2 STUBS
//Author: Dat Boi HQ
//Date: 10/08/2020
//Description: This is stubs for project 2

#include "Game.h"

#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
using namespace std;

int main () {
  srand(time(NULL));
  Game newGame;
  newGame.LoadShips();
  return 0;
}
