#include "point.h"
class Creature
{
private:
  Point location;
  int health = 100;
  double speed = 0;

public:
  Creature();
  Creature(Point _location, int _speed);
  ~Creature();
  Point GetLocation() { return location; }
  void SetLocation(Point _location) { this->location = _location; }
  double GetSpeed() { return this->speed; }
  void Move(int x, int y);
};
