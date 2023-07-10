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

Construct::~Construct()
{
}
