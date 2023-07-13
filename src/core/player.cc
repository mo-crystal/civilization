#include "player.h"

Player::Player(int _id, Point _location, int _speed) : Creature(_location, _speed)
{
  this->ID = _id;
}

Player::~Player()
{
}
