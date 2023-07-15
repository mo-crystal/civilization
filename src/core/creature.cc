#include "creature.h"

Creature::Creature()
{
}

Creature::Creature(Point _location, int _speed)
{
  this->location = _location;
  this->speed = _speed;
}

Creature::~Creature()
{
}
