class Point
{
private:
  double x, y;

public:
  Point();
  Point(double _x, double _y);
  ~Point();
  double GetX() const { return this->x; }
  double GetY() const { return this->y; }
  void SetX(double _x) { this->x = _x; }
  void SetY(double _y) { this->y = _y; }
  bool operator<(const Point &other) const { return this->x < other.x && this->y < other.y; }
  bool operator>(const Point &other) const { return this->x > other.x && this->y > other.y; }
  bool operator==(const Point &other) const { return this->x == other.x && this->y == other.y; }
};
