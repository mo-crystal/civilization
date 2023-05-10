#ifndef _STATIC_OBJ
#define _STATIC_OBJ

#include "string"
#include "vector"
#include "map"

#include "../utils/image.h"

class static_obj {
  int id;
  bool destroyable;
  block* location;
  std::string name;
  std::vector<image*> pic;
  std::map<int, int> contain;
};

#endif