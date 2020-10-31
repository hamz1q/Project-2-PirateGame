/*
 *Title: Game.cpp
 *Author: Hamza Qureshi
 *Email: hamz1@umbc.edu
 *Description: Member function implementation for the Game.h file for the Pirate project CMSC 202
 */

#include "Game.h"
//Constructor
Game::Game()
{
  GameTitle();
  LoadShips();
  LoadPirates();
}
//Name: LoadShip
//Desc: Loads ships from file into ship array
void Game::LoadShips()
{
  //string arrays to store ifstream data
  string cannon[MAX_SHIPS];
  string toughness[MAX_SHIPS];
  string speed[MAX_SHIPS];  
  ifstream myFile;
  
  myFile.open(PROJ2_SHIPS);
  if(myFile.is_open())
    {
      //looping through file and assigning member variables 
      for(int i = 0; i < MAX_SHIPS; i++)
	{
	  getline(myFile, m_ships[i].m_type, ',');
	  getline(myFile, cannon[i], ',');
	  //converting the strings to int 
	  m_ships[i].m_cannon = stoi(cannon[i]);
	  getline(myFile, toughness[i], ',');
	  m_ships[i].m_toughness = stoi(toughness[i]);
	  getline(myFile, speed[i], ',');
	  m_ships[i].m_speed = stoi(speed[i]);
	  getline(myFile, m_ships[i].m_desc);
	}

    }
  myFile.close();
  cout << MAX_SHIPS << " ships loaded." << endl;
 
}

//Name: LoadPirates
//Desc: Loads pirates from file into pirate array
void Game::LoadPirates()
{
  //declaring arrays to temporarily hold ifstream data
  string name[MAX_PIRATES];
  string rating[MAX_PIRATES];
  string origin[MAX_PIRATES];
  string desc[MAX_PIRATES];
  //delcaring int array to later convert string Rating 
  int rating2[MAX_PIRATES];
  ifstream myFile;
  
  myFile.open(PROJ2_PIRATES);
  if(myFile.is_open())
    {
      for(int i = 0; i < MAX_PIRATES; i++)
	{
	  getline(myFile, name[i], ',');
	  getline(myFile, rating[i], ',');
	  //converting string Rating to int Rating 
	  rating2[i] = stoi(rating[i]);
	  getline(myFile, origin[i], ',');
	  getline(myFile, desc[i]);
	  //Making pirate object using overloaded constructor
	  m_myPirate = Pirate(name[i], rating2[i], origin[i], desc[i]);
	  m_allPirates[i] = m_myPirate;
	  
	}

    }
  myFile.close();
  cout << MAX_PIRATES << " pirates loaded." << endl;
}

//Name: StartGame
//Desc: Assigns user random pirate and ship, calls and manages main menu
void Game::StartGame()
{
  //Randomly selecting an index value to pick a pirate and ship for the player
  int pirate_index = rand() % MAX_PIRATES;
  int ship_index = rand() % MAX_SHIPS;

  //Initializing the initial toughness for the user ship
  m_ships[ship_index].m_curToughness = m_ships[ship_index].m_toughness;
  
  //assigning random pirate and ship to the user
  m_myPirate = m_allPirates[pirate_index];
  m_myPirate.SetCurShip(m_ships[ship_index]);
  
  cout << "Congratulations! " << m_myPirate.GetName() << " is now available to Plunder!" << endl;
  cout << m_myPirate.GetName() << " is aboard a " << m_ships[ship_index].m_type << endl;
  
  int input = MainMenu();
  
  //Constantly checking if user chose "Retire" option  
  while(input != 4)
    {
      if(input == 1)
	{
	  SearchTreasure();
	  input = MainMenu();
	}
      else if(input == 2)
	{
	  m_myPirate.RepairShip();
	  input = MainMenu();
	}
      else if(input == 3)
	{
	  m_myPirate.DisplayScore();
	  input = MainMenu();
	}
      //Input validation for the main menu
      else if(input < 1 or input > 4)
	{
	  cout << "INVALID ENTRY! Choose options 1-4." << endl;
	  input = MainMenu();
	}
    }
  
  if(input == 4)
    {
      m_myPirate.DisplayScore();
      cout << m_myPirate.GetName() << " sails off into retirement!" << endl;
      cout << endl;
      cout << "Thanks for playing Pirates!" << endl;
    }
}

//Name: MainMenu
//Desc: Returns user options
int Game::MainMenu()
{
  //Declare variable that will return the user input 
  int user_input = 0;

  cout << "What will you like to do?" << endl;
  cout << "1. Search for treasure" << endl;
  cout << "2. Repair Ship" << endl;
  cout << "3. See Score" << endl;
  cout << "4. Retire" << endl;
  cout << endl;
  cin >> user_input;

  return user_input;
}

//Name: SearchTreasure
//Desc: Finds random enemy pirates, gives player to battle or flee from enemy
void Game::SearchTreasure()
{
  int input = 0;
  //Randomly selecting a number to pick an enemy pirate and enemy ship
  int enemyPirate = rand() % MAX_PIRATES;
  int enemyShip = rand() % MAX_SHIPS;
  
  //initializing the inital toughness for the enemy ship
  m_ships[enemyShip].m_curToughness = m_ships[enemyShip].m_toughness;
  
  //Passing randomly selected index to pirate and ships arrays to assign enemy
  cout << endl;
  cout << "You scan the horizon for prospective targets..." << endl;
  cout << "In the distance you see " << m_allPirates[enemyPirate].GetName() << " on a" << endl;
  cout << m_ships[enemyShip].m_type << "!" << endl;
  cout << endl;
  cout << "What would you like to do?" << endl;
  cout << "1. Attack " << m_allPirates[enemyPirate].GetName() << endl;
  cout << "2. Flee from " << m_allPirates[enemyPirate].GetName() << endl;
  cin >> input;

  //Input validation for battle and flee options
  while(input != 1 and input != 2)
    {
      cout << "INVALID CHOICE! Choose between 1 or 2." << endl;
      cout << "What would you like to do?" << endl;
      cout << "1. Attack " << m_allPirates[enemyPirate].GetName() << endl;
      cout << "2. Flee from " << m_allPirates[enemyPirate].GetName() << endl;
      cin >> input;
      break;
    }
  //Checking if user wants to flee or battle  
  if(input == 1)
    {
      m_myPirate.Battle(m_allPirates[enemyPirate], m_ships[enemyShip]);
    }
  else if(input == 2)
    {
      m_myPirate.Flee(m_allPirates[enemyPirate], m_ships[enemyShip]);
    }
  
}

