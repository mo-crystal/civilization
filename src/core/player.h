#include "creature.h"
#include "animation.h"
#include "item.h"

#define BAG_VOLUME 48

class Player : public Creature, public Animation
{
private:
  int ID = -1;
  Item bag[BAG_VOLUME];

public:
  Player(int _id, Point _location, int _speed = 5);
  ~Player();
  int GetID() { return ID; }
  Point GetLocation() { return Creature::GetLocation(); }
  void Move(Point p);
};
