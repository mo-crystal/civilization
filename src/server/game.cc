#include "game.h"

Game::Game()
{
}

Game::~Game()
{
}

bool Game::Load(std::string path="")
{
  for (int i = 0; i < MAP_WIDTH; i++)
  {
    for (int j = 0; j < MAP_HEIGHT; j++)
    {
      this->gameMap[i][j]=NULL;
    }
    
  }
  
  return true;
}

bool Game::Run()
{
  Player p(1,new Point(MAP_WIDTH/2,MAP_HEIGHT/2));
  this->AddPlayer(p);
  return true;
}

bool Game::Save()
{
  return true;
}

bool Game::AddPlayer(Player *p)
{
  if (std::find(this->playerList.begin(), this->playerList.end(), p) != playerList.end())
  {
    return false;
  }
  this->playerList.push_back(p);
  return true;
}