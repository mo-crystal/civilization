#include "game.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::SetPlayer(Player *p)
{
  if (this->myID == NO_PLAYER)
  {
    this->playerList.push_back(p);
    this->myID = p->GetID();
  }
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

Construct *Game::GetConstruct
{
  if (x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT)
  {
    return this->gameMap[x][y];
  }
  else
  {
    return NULL;
  }
}