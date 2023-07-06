#include "player.h"

Player::Player(int _id, Point _location) : Creature(_location)
{
  this->ID = _id;
}

Player::~Player()
{
}

