#include "item.h"

Item::Item(){

}

Item::Item(int _ID, std::string _name, int _maxStack, int _nowStack)
{
  this->ID = _ID;
  this->name = _name;
  this->maxStack = _maxStack;
  this->nowStack = _nowStack;
}

Item::~Item()
{
}
