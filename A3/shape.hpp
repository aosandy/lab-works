#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <iostream>
#include <memory>

namespace peskov
{
  struct point_t;
  struct rectangle_t;

  class Shape
  {
  public:
    using Ptr = std::shared_ptr<Shape>;
    virtual ~Shape() = default;

    virtual double getArea() const = 0;
    virtual rectangle_t getFrameRect() const = 0;
    virtual void move(const point_t& pos) = 0;
    virtual void move(double x, double y) = 0;
    virtual void scale(double k) = 0;
    virtual void print(std::ostream& out) const = 0;
  };
}

#endif
