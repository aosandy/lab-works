#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"
#include "base-types.hpp"

namespace peskov
{
  class Rectangle : public Shape
  {
  public:
    Rectangle(const point_t& pos, double width, double height);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t& pos) override;
    void move(double dx, double dy) override;
    void scale(double k) override;
    void print(std::ostream& out) const override;
    double getWidth() const;
    double getHeight() const;
    point_t getPos() const;
  private:
    point_t pos_;
    double width_, height_;
  };
}

#endif
