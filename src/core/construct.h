class Construct
{
private:
  int x, y;
  bool blockable = false;

public:
  Construct();
  Construct(int _x, int _y,bool _blockable);
  ~Construct();
  virtual bool TickAction() = 0;
  virtual bool Place() = 0;
  virtual bool Destory() = 0;
};
