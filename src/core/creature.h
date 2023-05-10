#ifndef _CREATURE
#define _CREATURE

#include "string"
#include "map"
#include "vector"

#include "../utils/image.h"

class creature {
  int id;
  double x, y;
  std::string name;
  std::map<std::string, std::vector<image*>> action;
  int max_health, now_health;
};

#endif