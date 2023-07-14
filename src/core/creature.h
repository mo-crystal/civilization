#include "point.h"
class Creature
{
private:
  Point location;
  int health = 100;
  double speed = 0;
  bool towards_horizontal = false;

public:
  Creature();
  Creature(Point _location, int _speed);
  ~Creature();
  void SetTowardsHorizontal(bool toward_h) { this->towards_horizontal = toward_h; }
  bool GetTowardsHorizontal() { return this->towards_horizontal; }
  Point GetLocation() { return location; }
  void SetLocation(Point _location) { this->location = _location; }
  double GetSpeed() { return this->speed; }
  void Move(int x, int y);
};
