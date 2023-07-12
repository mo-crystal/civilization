#include <list>
#include <map>
#include <ctime>

#include "../core/construct.h"
#include "../core/player.h"

#define MAP_WIDTH 256
#define MAP_HEIGHT 256

class Game
{
private:
  Construct *gameMap[MAP_WIDTH][MAP_HEIGHT];
  std::list<Player *> playerList;
  int myID = NO_PLAYER;
  Player *me = NULL;
  std::map<Point, int> decorates;

public:
  Game();
  ~Game();
  void DecorateInit(int block_size);
  void SetMap() {}
  void SetPlayer(Player *p);
  bool AddPlayer(Player *p);
  std::map<Point, int> GetDecorate(Point left_top, Point right_down);
  Construct *GetConstruct(int x, int y);
  Player GetPlayer() { return *(this->me); }
};
