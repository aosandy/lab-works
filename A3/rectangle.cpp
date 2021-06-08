#include "rectangle.hpp"

#include <iosfwd>
#include <stdexcept>

peskov::Rectangle::Rectangle(const point_t &pos, double width, double height) :
  pos_(pos),
  width_(width),
  height_(height)
{
  if (width_ <= 0.0 || height_ <= 0.0)
  {
    throw std::invalid_argument("Parameters are not positive.");
  }
}

double peskov::Rectangle::getArea() const
{
  return width_ * height_;
}

peskov::rectangle_t peskov::Rectangle::getFrameRect() const
{
  return { width_, height_, pos_ };
}

void peskov::Rectangle::move(const point_t& pos)
{
  pos_ = pos;
}

void peskov::Rectangle::move(double dx, double dy)
{
  pos_.x += dx;
  pos_.y += dy;
}

void peskov::Rectangle::scale(double k)
{
  if (k <= 0)
  {
    throw std::invalid_argument("Coefficient is not positive.");
  }
  width_ *= k;
  height_ *= k;
}

void peskov::Rectangle::print(std::ostream& out) const
{
  out << "Width: " << width_ << '\n'
      << "Height: " << height_ << '\n'
      << "Position: (" << pos_.x << "; "
      << pos_.y << ")\n";
}

double peskov::Rectangle::getWidth() const
{
  return width_;
}

double peskov::Rectangle::getHeight() const
{
  return height_;
}

peskov::point_t peskov::Rectangle::getPos() const
{
  return pos_;
}
