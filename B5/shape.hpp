#ifndef B5_SHAPE_HPP
#define B5_SHAPE_HPP

#include <vector>
#include <iostream>

struct Point
{
  int x, y;

  friend std::istream& operator>>(std::istream&, Point&);
  friend std::ostream& operator<<(std::ostream&, const Point&);
};

using Shape = std::vector<Point>;

std::istream &operator>>(std::istream&, Shape&);
std::ostream &operator<<(std::ostream&, const Shape&);

struct ShapesComparator
{
  bool operator ()(const Shape&, const Shape&) const;
};

bool isTriangle(const Shape&);
bool isSquare(const Shape&);
bool isRectangle(const Shape&);
bool isPentagon(const Shape&);

namespace details
{
  const size_t TRIANGLE_VERTICES = 3;
  const size_t QUADRANGLE_VERTICES = 4;
  const size_t PENTAGON_VERTICES = 5;
  const char OPENING_BRACKET = '(';
  const char CLOSING_BRACKET = ')';
  const char DELIMETER = ';';

  size_t getSquaredDist(const Point&, const Point&);
}

#endif
