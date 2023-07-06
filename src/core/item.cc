#include"item.h" 

Item::Item(int _ID,std::string _name,int _maxStack)
{
  this->ID=ID;
  this->name=_name;
  this->maxStack=_maxStack;
}

Item::~Item()
{
}
