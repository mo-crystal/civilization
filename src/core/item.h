#include <iostream>

class Item
{
private:
  int ID;
  std::string name;
  int maxStack = 1;
  int nowStack = 1;
  double Durability = -1;

public:
  Item(int _ID, std::string _name, int _maxStack);
  ~Item();
  bool IsMax() { return maxStack == nowStack; }
};