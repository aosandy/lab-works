#define _USE_MATH_DEFINES

#include "circle.hpp"
#include <iosfwd>
#include <stdexcept>
#include <cmath>

peskov::Circle::Circle(const point_t& pos, double radius) :
  pos_(pos),
  radius_(radius)
{
  if (radius_ <= 0.0)
  {
    throw std::invalid_argument("Radius is not positive.");
  }
}

double peskov::Circle::getArea() const
{
  return radius_ * radius_ * M_PI;
}

peskov::rectangle_t peskov::Circle::getFrameRect() const
{
  return { 2 * radius_, 2 * radius_ , pos_ };
}

void peskov::Circle::move(const point_t& pos)
{
  pos_ = pos;
}

void peskov::Circle::move(double dx, double dy)
{
  pos_.x += dx;
  pos_.y += dy;
}

void peskov::Circle::scale(double k)
{
  if (k <= 0)
  {
    throw std::invalid_argument("Coefficient is not positive.");
  }
  radius_ *= k;
}


void peskov::Circle::print(std::ostream& out) const
{
  out << "Radius: " << radius_ << '\n'
      << "Position: (" << pos_.x << "; "
      << pos_.y << ")\n";
}

double peskov::Circle::getRadius() const
{
  return radius_;
}

peskov::point_t peskov::Circle::getPos() const
{
  return pos_;
}
