#ifndef _CHUNK0
#define _CHUNK0

#include "block.h"

class chunk0 {
  long x, y;
  block* contain[16][16];
  unsigned char r, g, b;
  int owner; // reference to uid
  bool is_foundation;
};

#endif