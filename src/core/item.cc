#include "item.h"

Item::Item(int _ID, std::string _name, int _maxStack, int _nowStack = 1)
{
  this->ID = _ID;
  this->name = _name;
  this->maxStack = _maxStack;
  this->nowStack = _nowStack;
}

Item::~Item()
{
}
