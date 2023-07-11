#include "point.h"
class Creature
{
private:
  Point location;
  int health = 100;
  int speed = 0;

public:
  Creature();
  Creature(Point _location);
  ~Creature();
  Point GetLocation() { return location; }
};
