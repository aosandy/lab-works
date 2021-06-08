#include "circle.hpp"

#define _USE_MATH_DEFINES
#include <cmath>
#include <cassert>

Circle::Circle(const point_t &pos, double radius) :
  pos_(pos),
  radius_(radius)
{
  assert(radius_ > 0.0);
}

double Circle::getArea() const
{
  return radius_ * radius_ * M_PI;
}

rectangle_t Circle::getFrameRect() const
{
  return { 2 * radius_, 2 * radius_ , pos_ };
}

void Circle::move(const point_t &pos)
{
  pos_ = pos;
}

void Circle::move(double dx, double dy)
{
  pos_.x += dx;
  pos_.y += dy;
}

void Circle::print(std::ostream& out) const
{
  out << "Radius: " << radius_ << '\n'
      << "Position: (" << pos_.x << "; "
      << pos_.y << ")\n";
}

double Circle::getRadius() const
{
  return radius_;
}

point_t Circle::getPos() const
{
  return pos_;
}
