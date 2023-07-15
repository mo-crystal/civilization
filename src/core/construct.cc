#include "construct.h"

Construct::Construct()
{
}

Construct::Construct(int _x, int _y, bool _blockable)
{
  this->x = _x;
  this->y = _y;
  this->blockable = _blockable;
}

bool Construct::SetOwnerID(int ID)
{
  if (this->ownerID == 0)
  {
    this->ownerID = ID;
    return true;
  }
  return false;
}

Construct::~Construct()
{
}
