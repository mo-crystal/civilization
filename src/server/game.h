#include<list>

#include"../core/construct.h"
#include"../core/player.h"


class Game
{
private:
  Construct* gameMap[256][256];
  std::list<> tickList;
  std::list<Player*> playerList;
public:
  Game();
  ~Game();
  bool Load();
  bool Save();
};
