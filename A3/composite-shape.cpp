#include "composite-shape.hpp"

#include <stdexcept>
#include <iosfwd>
#include <memory>
#include <algorithm>

#include "base-types.hpp"

peskov::CompositeShape::CompositeShape():
  size_(0)
{
}

peskov::CompositeShape::CompositeShape(const CompositeShape& shape):
  size_(shape.size_)
{
  if (shape.size_ > 0)
  {
    shapes_ = std::make_unique<Ptr[]>(shape.size_);
    for (size_t i = 0; i < shape.size_; i++)
    {
      shapes_[i] = shape.shapes_[i];
    }
  }
}

peskov::CompositeShape::CompositeShape(CompositeShape&& shape) noexcept:
  shapes_(std::move(shape.shapes_)),
  size_(shape.size_)
{
  shape.size_ = 0;
}

peskov::CompositeShape& peskov::CompositeShape::operator=(const CompositeShape& shape)
{
  if (this == &shape)
  {
    return *this;
  }
  if (shape.size_ > 0)
  {
    shapes_ = std::make_unique<Ptr[]>(shape.size_);
    size_ = shape.size_;
    for (size_t i = 0; i < shape.size_; i++)
    {
      shapes_[i] = shape.shapes_[i];
    }
  }
  else
  {
    shapes_ = nullptr;
    size_ = 0;
  }
  return *this;
}

peskov::CompositeShape& peskov::CompositeShape::operator=(CompositeShape&& shape) noexcept
{
  if (this == &shape)
  {
    return *this;
  }
  shapes_ = std::move(shape.shapes_);
  size_ = shape.size_;
  shape.size_ = 0;
  return *this;
}

peskov::Shape::Ptr peskov::CompositeShape::operator[](size_t index) const
{
  if (index >= size_)
  {
    throw std::out_of_range("Index is out of range.");
  }
  return shapes_[index];
}

double peskov::CompositeShape::getArea() const
{
  double area = 0.0;
  for (size_t i = 0; i < size_; i++)
  {
    area += shapes_[i]->getArea();
  }
  return area;
}

peskov::rectangle_t peskov::CompositeShape::getFrameRect() const
{
  if (size_ == 0)
  {
    throw std::length_error("Composite Shape is empty.");
  }
  rectangle_t rect = shapes_[0]->getFrameRect();
  double posX = rect.pos.x;
  double posY = rect.pos.y;
  double halfWidth = rect.width / 2.0;
  double halfHeight = rect.width / 2.0;

  double minX = posX - halfWidth;
  double maxX = posX + halfWidth;
  double minY = posY - halfHeight;
  double maxY = posY + halfHeight;
  for (size_t i = 1; i < size_; i++)
  {
    rect = shapes_[i]->getFrameRect();
    posX = rect.pos.x;
    posY = rect.pos.y;
    halfWidth = rect.width / 2.0;
    halfHeight = rect.width / 2.0;

    minX = std::min(minX, posX - halfWidth);
    maxX = std::max(maxX, posX + halfWidth);
    minY = std::min(minY, posY - halfHeight);
    maxY = std::max(maxY, posY + halfHeight);
  }
  const point_t pos { (maxX + minX) / 2.0, (maxY + minY) / 2.0 };
  return { maxX - minX, maxY - minY, pos};
}

void peskov::CompositeShape::move(const peskov::point_t& pos)
{
  if (size_ == 0)
  {
    throw std::length_error("Composite Shape is empty.");
  }
  const point_t compShapePos = getFrameRect().pos;
  move(pos.x - compShapePos.x, pos.y - compShapePos.y);
}

void peskov::CompositeShape::move(double dx, double dy)
{
  if (size_ == 0)
  {
    throw std::length_error("Composite Shape is empty.");
  }
  for (size_t i = 0; i < size_; i++)
  {
    shapes_[i]->move(dx, dy);
  }
}

void peskov::CompositeShape::scale(double k)
{
  if (size_ == 0)
  {
    throw std::length_error("Composite Shape is empty.");
  }
  if (k <= 0)
  {
    throw std::invalid_argument("Coefficient is not positive.");
  }
  const point_t compShapePos = getFrameRect().pos;
  for (size_t i = 0; i < size_; i++)
  {
    point_t currPos = shapes_[i]->getFrameRect().pos;
    currPos.x = compShapePos.x + ((currPos.x - compShapePos.x) * k);
    currPos.y = compShapePos.y + ((currPos.y - compShapePos.y) * k);
    shapes_[i]->scale(k);
    shapes_[i]->move(currPos);
  }
}

void peskov::CompositeShape::print(std::ostream& out) const
{
  for (size_t i = 0; i < size_; i++)
  {
    out << "Figure " << i << ":\n";
    shapes_[i]->print(out);
  }
}

void peskov::CompositeShape::add(const Shape::Ptr& shape)
{
  if (shape == nullptr)
  {
    throw std::invalid_argument("New shape is empty.");
  }
  if (this == shape.get())
  {
    throw std::invalid_argument("New shape matches with the composite shape.");
  }
  std::unique_ptr<Ptr[]> temp(std::make_unique<Ptr[]>(size_ + 1));
  for (size_t i = 0; i < size_; i++)
  {
    if (shapes_[i].get() == shape.get())
    {
      throw std::invalid_argument("Composite Shape already contains this shape.");
    }
    temp[i] = shapes_[i];
  }
  shapes_ = std::move(temp);
  shapes_[size_++] = shape;
}

void peskov::CompositeShape::remove(size_t index)
{
  if (size_ == 0)
  {
    throw std::length_error("Composite Shape is empty.");
  }
  if (index >= size_)
  {
    throw std::out_of_range("Index is out of range.");
  }
  for (size_t i = index + 1; i < size_; i++)
  {
    shapes_[i - 1] = std::move(shapes_[i]);
  }
  size_--;
}

size_t peskov::CompositeShape::getSize() const
{
  return size_;
}
