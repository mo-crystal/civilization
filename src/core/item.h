#include <iostream>

class Item
{
private:
  int ID = -1;
  std::string name = "";
  int maxStack = 1;
  int nowStack = 1;
  double Durability = -1;

public:
  Item();
  Item(int _ID, std::string _name, int _maxStack, int _nowStack = 1);
  ~Item();
  int GetID() { return this->ID; }
  std::string GetName() { return this->name; }
  int GetNowStack() { return this->nowStack; }
  int GetMax() { return this->maxStack; }
  void SetDurability(double d) { this->Durability = d; }
  double GetDurability() { return this->Durability; }
  bool IsMax() { return maxStack >= nowStack; }
  bool operator==(const Item &other) { return (this->ID == other.ID && this->name == other.name); }
  bool IsValid() { return ID > 0; }
};