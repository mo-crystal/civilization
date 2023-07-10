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

public:
  Game();
  ~Game();
  bool Load(std::string path = "");
  bool Run();
  bool Save();
  bool AddPlayer(Player *p);
};
