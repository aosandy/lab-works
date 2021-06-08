#include <iostream>
#include "shape.hpp"
#include "rectangle.hpp"
#include "circle.hpp"

void testShapeMove(Shape* shape, const double xMove, const double yMove, const point_t moveRectPos);
void testShapeFrameRect(Shape* shape);

int main()
{
  const double width = 12.5;
  const double height = 54.11;
  const double xRectPos = 3.82;
  const double yRectPos = 7;
  const point_t rectPos = { xRectPos, yRectPos };

  Rectangle rectangle(rectPos, width, height);
  Shape* shape = &rectangle;

  std::cout << "Rectangle area: " << shape->getArea() << '\n';
  shape->print(std::cout);
  std::cout << '\n';

  double xMove = -12.32;
  double yMove = 1.111;
  const point_t moveRectPos = { xMove, yMove };
  xMove = 28;
  yMove = 4;
  testShapeMove(shape, xMove, yMove, moveRectPos);

  testShapeFrameRect(shape);

  const double radius = 10.01;
  const double xCirclePos = 23;
  const double yCirclePos = 43.983;
  const point_t circlePos = { xCirclePos, yCirclePos };

  Circle circle(circlePos, radius);
  shape = &circle;

  std::cout << "Circle area: " << shape->getArea() << '\n';
  shape->print(std::cout);
  std::cout << '\n';

  xMove = 32.999;
  yMove = 0;
  const point_t moveCirclePos = { xMove, yMove };
  xMove = -52.12;
  yMove = 12.3;
  testShapeMove(shape, xMove, yMove, moveRectPos);

  testShapeFrameRect(shape);

  return 0;
}

void testShapeMove(Shape* shape, const double xMove, const double yMove, const point_t moveRectPos)
{
  std::cout << "Move to (x + " << xMove << "; y + " << yMove << ")" << '\n';
  shape->move(xMove, yMove);
  shape->print(std::cout);
  std::cout << "Move to (" << moveRectPos.x << "; " << moveRectPos.y << ")" << '\n';
  shape->move(moveRectPos);
  shape->print(std::cout);
  std::cout << '\n';
}

void testShapeFrameRect(Shape* shape)
{
  const rectangle_t frameRect = shape->getFrameRect();
  std::cout << "Rectangle frame width: " << frameRect.width << '\n'
            << "Rectangle frame height: " << frameRect.height << '\n'
            << "Rectangle frame pos(x): " << frameRect.pos.x << '\n'
            << "Rectangle frame pos(y): " << frameRect.pos.y << '\n' << '\n';
}