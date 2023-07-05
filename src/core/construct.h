class Construct
{
private:
  int x, y;

public:
  Construct();
  Construct(int _x, int _y);
  ~Construct();
  virtual bool TickAction() = 0;
  virtual bool Place() = 0;
  virtual bool Destory() = 0;
};
