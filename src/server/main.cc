#include "../utils/log.h"
#include"game.h"
int main() {
  info("server starting...");
  Game g;
  g.Load();
  g.Run();
  g.Save();
  info("server ended.");
  return 0;
}
