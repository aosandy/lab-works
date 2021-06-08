#include <iostream>
#include <memory>
#include <stdexcept>
#include "shape.hpp"
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"

void testShapeMove(peskov::Shape* shape, const double xMove, const double yMove, const peskov::point_t moveRectPos);
void testShapeFrameRect(peskov::Shape* shape);
void testScaling(peskov::Shape* shape, const double k);

int main()
{
  try
  {
    const double width = 12.5;
    const double height = 54.11;
    const double xRectPos = 3.82;
    const double yRectPos = 7;
    const peskov::point_t rectPos = {xRectPos, yRectPos};

    peskov::Rectangle rectangle(rectPos, width, height);
    peskov::Shape *shape = &rectangle;

    std::cout << "Rectangle area: " << shape->getArea() << '\n';
    shape->print(std::cout);
    std::cout << '\n';

    double xMove = -12.32;
    double yMove = 1.111;
    const peskov::point_t moveRectPos = {xMove, yMove};
    xMove = 28;
    yMove = 4;
    testShapeMove(shape, xMove, yMove, moveRectPos);

    testShapeFrameRect(shape);

    const double scalingFactor = 2.5;
    testScaling(shape, scalingFactor);
  }
  catch (const std::exception& ex)
  {
    std::cerr << ex.what() << '\n';
    return 1;
  }

  try
  {
    const double radius = 10.01;
    const double xCirclePos = 23;
    const double yCirclePos = 43.983;
    const peskov::point_t circlePos = {xCirclePos, yCirclePos};

    peskov::Circle circle(circlePos, radius);
    peskov::Shape *shape = &circle;

    std::cout << "Circle area: " << shape->getArea() << '\n';
    shape->print(std::cout);
    double xMove = 32.999;
    double yMove = 0;
    const peskov::point_t moveCirclePos = {xMove, yMove};
    xMove = -52.12;
    yMove = 12.3;
    testShapeMove(shape, xMove, yMove, moveCirclePos);

    testShapeFrameRect(shape);

    const double scalingFactor = 0.87;
    testScaling(shape, scalingFactor);
  }
  catch (const std::exception& ex)
  {
    std::cerr << ex.what() << '\n';
    return 1;
  }
  try
  {
    const double width = 12.5;
    const double height = 54.11;
    const double xRectPos = 3.82;
    const double yRectPos = 7;
    const peskov::point_t rectPos = {xRectPos, yRectPos};
    peskov::Rectangle rectangle(rectPos, width, height);

    const double radius = 10.01;
    const double xCirclePos = 23;
    const double yCirclePos = 43.983;
    const peskov::point_t circlePos = {xCirclePos, yCirclePos};
    peskov::Circle circle(circlePos, radius);

    peskov::Shape::Ptr rectPtr = std::make_shared<peskov::Rectangle>(rectangle);
    peskov::Shape::Ptr circlePtr = std::make_shared<peskov::Circle>(circle);

    peskov::CompositeShape testCompShape;
    testCompShape.add(rectPtr);
    testCompShape.add(circlePtr);
    testCompShape.print(std::cout);
    const peskov::point_t movePos = { 4.23, 764.7};
    const double coefficient = 5.67;
    std::cout << "Moving and scaling the Composite Shape\n";
    testCompShape.move(movePos);
    testCompShape.scale(coefficient);
    testCompShape.print(std::cout);
    std::cout << '\n';
  }
  catch (const std::exception& ex)
  {
    std::cerr << ex.what() << '\n';
    return 1;
  }
  return 0;
}

void testShapeMove(peskov::Shape* shape, const double xMove, const double yMove, const peskov::point_t moveRectPos)
{
  std::cout << "Move to (x + " << xMove << "; y + " << yMove << ")" << '\n';
  shape->move(xMove, yMove);
  shape->print(std::cout);
  std::cout << '\n';
  std::cout << "Move to (" << moveRectPos.x << "; " << moveRectPos.y << ")" << '\n';
  shape->move(moveRectPos);
  shape->print(std::cout);
  std::cout << '\n';
}

void testShapeFrameRect(peskov::Shape* shape)
{
  const peskov::rectangle_t frameRect = shape->getFrameRect();
  std::cout << "Rectangle frame width: " << frameRect.width << '\n'
            << "Rectangle frame height: " << frameRect.height << '\n'
            << "Rectangle frame position: (" << frameRect.pos.x << "; "
            << frameRect.pos.y << "* )\n\n";
}

void testScaling(peskov::Shape* shape, const double k)
{
  std::cout << "Shape scaling with factor " << k << '\n';
  shape->scale(k);
  shape->print(std::cout);
  std::cout << '\n';
}
