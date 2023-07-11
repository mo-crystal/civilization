#define NO_PLAYER 0

class Construct
{
private:
  int x, y;
  bool blockable = false;
  int ownerID = NO_PLAYER;

public:
  Construct();
  Construct(int _x, int _y, bool _blockable);
  ~Construct();
  bool SetOwnerID(int ID);
  virtual bool TickAction() = 0;
  virtual bool Place() = 0;
  virtual bool Destory() = 0;
};
