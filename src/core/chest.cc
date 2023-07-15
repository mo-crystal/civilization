#include "chest.h"

Chest::Chest(int _capacity)
{
  this->capacity = _capacity;
  this->contents = new Item[this->capacity];
}

Chest::~Chest()
{
}
