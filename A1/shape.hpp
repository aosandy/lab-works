#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <iostream>

struct point_t;
struct rectangle_t;

class Shape
{
public:
  virtual ~Shape() = default;
  virtual double getArea() const = 0;
  virtual rectangle_t getFrameRect() const = 0;
  virtual void move(const point_t &pos) = 0;
  virtual void move(const double x, const double y) = 0;
  virtual void scale(const double k) = 0;
  virtual void print(std::ostream& out) const = 0;
};

#endif
