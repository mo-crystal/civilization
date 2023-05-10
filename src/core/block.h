#ifndef _BLOCK
#define _BLOCK

#include "static_obj.h"
#include "chunk0.h"

class block {
  long x, y;
  static_obj* contain;
  chunk0* location;
  int abundance;
};

#endif