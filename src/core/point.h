class Point
{
private:
  double x, y;

public:
  Point();
  Point(double _x, double _y);
  ~Point();
  double GetX() { return this->x; }
  double GetY() { return this->y; }
  void SetX(double _x) { this->x = _x; }
  void SetY(double _y) { this->y = _y; }
};
