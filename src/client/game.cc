#include "game.h"

Game::Game()
{
}

Game::~Game()
{
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