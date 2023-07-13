#include "game.h"

Game::Game()
{
}

Game::~Game()
{
}

std::map<Point, int> Game::DecorateInit(int block_size)
{
  srand(time(0));
  this->decorates.insert(std::pair<Point, int>(Point(256 * 64 / 2, 256 * 64 / 2), rand() % 7));
  int size = rand() % (MAP_WIDTH * MAP_HEIGHT / 4) + MAP_WIDTH;
  for (int i = 0; i < size; i++)
  {
    int x = block_size + rand() % (block_size * MAP_WIDTH - 2 * block_size);
    int y = block_size + rand() % (block_size * MAP_HEIGHT - 2 * block_size);
    this->decorates.insert(std::pair<Point, int>(Point(x, y), rand() % 7));
  }
  return this->decorates;
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

std::map<Point, int> Game::GetDecorate(Point left_top, Point right_down)
{
  std::map<Point, int> res;
  for (auto i = this->decorates.begin(); i != this->decorates.end(); i++)
  {
    if ((*i).first > left_top && (*i).first < right_down)
    {
      res.insert(*i);
    }
  }
  return res;
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