#include <list>
#include <map>
#include <ctime>
#include <algorithm>

#include "../core/construct.h"
#include "../core/player.h"
#include "../core/animation.h"

#define MAP_WIDTH 256
#define MAP_HEIGHT 256
#define UP 1
#define RIGHT 2
#define DOWN 3
#define LEFT 4

class Game
{
private:
  Construct *gameMap[MAP_WIDTH][MAP_HEIGHT];
  std::list<Player *> playerList;
  int myID = NO_PLAYER;
  Player *me = NULL;
  std::map<Point, int> decorates;
  int map_x_min = 0, map_y_min = 0, map_x_max = 0, map_y_max = 0;
  int block_size = 64;

public:
  Game();
  ~Game();
  std::map<Point, int> DecorateInit(int block_size);
  void SetMapRange(int _block_size);
  void SetMap()
  { /*TODO:与服务器建立连接后初始化*/
  }
  void SetPlayer(Player *p);
  bool AddPlayer(Player *p);
  std::map<Point, int> GetDecorate(Point left_top, Point right_down);
  Construct *GetConstruct(int x, int y);
  Player GetPlayer() { return *(this->me); }
  void PlayerMove(int playerID, int direction);
  bool Block(Point p1, Point p2);
};
