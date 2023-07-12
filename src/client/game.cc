#include "game.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::DecorateInit(int block_size)
{
  srand(time(0));
  int size = rand() % (MAP_WIDTH * MAP_HEIGHT / 4) + MAP_WIDTH;
  for (int i = 0; i < size; i++)
  {
    int x = rand() % (block_size * MAP_WIDTH);
    int y = rand() % (block_size * MAP_HEIGHT);
    if (x < block_size || y < block_size || x - block_size > MAP_WIDTH * block_size || y - block_size > MAP_HEIGHT * block_size)
    {
      continue;
    }
    this->decorates.insert(Point(x, y), rand() % 7);
  }
}

void Game::SetPlayer(Player *p)
{
  if (this->myID == NO_PLAYER)
  {
    this->me = p;
    this->myID = p->GetID();
  }
}

bool Game::AddPlayer(Player *p)
{
  // TODO:判断重复
  this->playerList.push_back(p);
  return true;
}

Construct *Game::GetConstruct(int x, int y)
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