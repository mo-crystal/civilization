#ifndef _ITEM
#define _ITEM

#include "string"
#include "../utils/image.h"

class item {
  int id;
  std::string name;
  image* pic;
  int max_count; // 最大堆叠数
};

#endif