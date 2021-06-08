#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP

#include <memory>

#include "shape.hpp"

namespace peskov
{
  class CompositeShape : public Shape
  {
  public:
    CompositeShape();
    CompositeShape(const CompositeShape& shape);
    CompositeShape(CompositeShape&& shape) noexcept;
    ~CompositeShape() override = default;

    CompositeShape& operator=(const CompositeShape& shape);
    CompositeShape& operator=(CompositeShape&& shape) noexcept;
    Shape::Ptr operator[](size_t index) const;

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t& pos) override;
    void move(double dx, double dy) override;
    void scale(double k) override;
    void print(std::ostream& out) const override;
    void add(const Shape::Ptr& shape);
    void remove(size_t index);
    size_t getSize() const;

  private:
    std::unique_ptr<Ptr[]> shapes_;
    size_t size_;
  };
}

#endif
