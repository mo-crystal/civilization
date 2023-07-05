#include "game.h"

Game::Game()
{
}

Game::~Game()
{
}

bool Game::Load()
{
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