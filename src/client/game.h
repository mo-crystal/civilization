#include "../core/construct.h"
#include "../core/player.h"

#define MAP_WIDTH 256
#define MAP_HEIGHT 256

class Game
{
private:
  Construct *gameMap[MAP_WIDTH][MAP_HEIGHT];
  Player p;

public:
  Game();
  ~Game();
  void SetPlayer(Player _p) { this->p = _p; }
  void SetMap() {}
  Construct *GetConstruct(int x, int y);
};
