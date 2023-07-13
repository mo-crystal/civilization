#include "game.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::SetMapRange(int _block_size)
{
  map_x_max = MAP_WIDTH * _block_size;
  map_y_max = MAP_HEIGHT * _block_size;
  block_size = _block_size;
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
    playerList.push_back(p);
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

void Game::PlayerMove(int playerID, int direction)
{
  for (auto it = playerList.begin(); it != playerList.end(); it++)
  {
    if ((*it)->GetID() == playerID)
    {
      double speed = (*it)->GetSpeed();
      if (direction == UP)
      {
        Point new_p((*it)->GetLocation().GetX(), (*it)->GetLocation().GetY() - speed);
        if (new_p.GetY() >= map_y_min && !Block((*it)->GetLocation(), new_p))
        {
          (*it)->Move(new_p);
        }
      }
      else if (direction == DOWN)
      {
        Point new_p((*it)->GetLocation().GetX(), (*it)->GetLocation().GetY() + speed);
        if (new_p.GetY() < map_y_max && !Block((*it)->GetLocation(), new_p))
        {
          (*it)->Move(new_p);
        }
      }
      else if (direction == LEFT)
      {
        Point new_p((*it)->GetLocation().GetX() - speed, (*it)->GetLocation().GetY());
        if (new_p.GetX() >= map_x_min && !Block((*it)->GetLocation(), new_p))
        {
          (*it)->Move(new_p);
        }
      }
      else if (direction == RIGHT)
      {
        Point new_p((*it)->GetLocation().GetX() + speed, (*it)->GetLocation().GetY());
        if (new_p.GetX() < map_x_max && !Block((*it)->GetLocation(), new_p))
        {
          (*it)->Move(new_p);
        }
      }
      else
      {
      }
    }
  }
}

bool Game::Block(Point p1, Point p2)
{
  // 目前不能斜向移动 可以先不判定 后续有需求改这
  if (p1.GetX() != p2.GetX() && p1.GetY() != p2.GetY())
  {
    return false;
  }
  else if (p1.GetX() != p2.GetX())
  {
    int min_b = std::min(p1.GetX(), p2.GetX()) / block_size;
    int max_b = std::max(p1.GetX(), p2.GetX()) / block_size;
    int y = p1.GetY() / block_size;
    for (int i = min_b; i <= max_b; i++)
    {
      if (gameMap[i][y] != NULL && gameMap[i][y]->IsBlock())
      {
        return true;
      }
    }
    return false;
  }
  else if (p1.GetY() != p2.GetY())
  {
    int min_b = std::min(p1.GetY(), p2.GetY()) / block_size;
    int max_b = std::max(p1.GetY(), p2.GetY()) / block_size;
    int x = p1.GetX() / block_size;
    for (int i = min_b; i <= max_b; i++)
    {
      if (gameMap[x][i] != NULL && gameMap[x][i]->IsBlock())
      {
        return true;
      }
    }
    return false;
  }
  return true;
}