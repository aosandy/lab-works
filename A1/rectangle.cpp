#include "rectangle.hpp"

#include <cassert>

Rectangle::Rectangle(const point_t &pos, double width, double height) :
  pos_(pos),
  width_(width),
  height_(height)
{
  assert((width_ > 0.0) && (height_ > 0.0));
}

double Rectangle::getArea() const
{
  return width_ * height_;
}

rectangle_t Rectangle::getFrameRect() const
{
  return {width_, height_, pos_};
}

void Rectangle::move(const point_t& pos)
{
  pos_ = pos;
}

void Rectangle::move(double dx, double dy)
{
  pos_.x += dx;
  pos_.y += dy;
}

void Rectangle::scale(const double k)
{
  width_ *= k;
  height_ *= k;
}

void Rectangle::print(std::ostream& out) const
{
  out << "Width: " << width_ << '\n'
      << "Height: " << height_ << '\n'
      << "Position: (" << pos_.x << "; "
      << pos_.y << ")\n";
}

double Rectangle::getWidth() const
{
  return width_;
}

double Rectangle::getHeight() const
{
  return height_;
}

point_t Rectangle::getPos() const
{
  return pos_;
}
