#include <list>

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

public:
  Game();
  ~Game();
  void SetMap() {}
  void SetPlayer(Player *p);
  bool AddPlayer(Player *p);
  Construct *GetConstruct(int x, int y);
  Player GetPlayer() { return this->p; }
};
