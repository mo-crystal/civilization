#include "creature.h"
#include "item.h"

#define BAG_VOLUME 48

class Player : public Creature
{
private:
  int ID = -1;
  Item bag[BAG_VOLUME];

public:
  Player(int _id, Point _location);
  ~Player();
  int GetID() { return ID; }
};
