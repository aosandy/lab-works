#include "shape.hpp"

#include <iostream>
#include <iterator>
#include <boost/io/ios_state.hpp>

#include "utility.hpp"

std::istream &operator>>(std::istream &input, Point &point)
{
  std::istream::sentry sentry(input);
  if (!sentry)
  {
    return input;
  }
  boost::io::ios_flags_saver saver(input);
  input >> std::noskipws >> skipWS;
  if (!input || (input.get() != details::OPENING_BRACKET))
  {
    input.setstate(std::ios::failbit);
    return input;
  }
  int x;
  input >> skipWS >> x;
  if (!input || ((input >> skipWS).get() != details::DELIMETER))
  {
    input.setstate(std::ios::failbit);
    return input;
  }
  int y;
  input >> skipWS >> y;
  if (!input || ((input >> skipWS).get() != details::CLOSING_BRACKET))
  {
    input.setstate(std::ios::failbit);
    return input;
  }
  point.x = x;
  point.y = y;
  return input;
}

std::ostream &operator<<(std::ostream &output, const Point &point)
{
  std::ostream::sentry sentry(output);
  if (!sentry)
  {
    return output;
  }
  const char DELIMETER = ';';
  output << '(' << point.x << DELIMETER << point.y << ')';
  return output;
}

std::istream &operator>>(std::istream &input, Shape &shape)
{
  std::istream::sentry sentry(input);
  if (!sentry)
  {
    return input;
  }
  boost::io::ios_flags_saver saver(input);
  input >> std::noskipws;
  size_t vertices;
  if (!(input >> std::ws >> vertices) || (vertices == 0))
  {
    input.setstate(std::ios::failbit);
    return input;
  }

  Shape temp(vertices);
  for (size_t i = 0; i < vertices; ++i)
  {
    if (!(input >> temp[i]))
    {
      return input;
    }
  }
  shape = std::move(temp);
  return input;
}

std::ostream &operator<<(std::ostream &output, const Shape &shape)
{
  std::ostream::sentry sentry(output);
  if (!sentry)
  {
    return output;
  }
  output << shape.size() << ' ';
  std::copy(shape.begin(), shape.end(), std::ostream_iterator<Point>(output, " "));
  return output;
}

bool ShapesComparator::operator()(const Shape &shape1, const Shape &shape2) const
{
  if ((shape1.size() == details::QUADRANGLE_VERTICES) && (shape2.size() == details::QUADRANGLE_VERTICES))
  {
    return isSquare(shape1) && !isSquare(shape2);
  }
  return shape1.size() < shape2.size();
}

bool isTriangle(const Shape &shape)
{
  return shape.size() == details::TRIANGLE_VERTICES;
}

bool isSquare(const Shape &shape)
{
  const size_t squaredSide1 = details::getSquaredDist(shape[0], shape[1]);
  const size_t squaredSide2 = details::getSquaredDist(shape[1], shape[2]);
  return isRectangle(shape) && (squaredSide1 == squaredSide2);
}

bool isRectangle(const Shape &shape)
{
  if (shape.size() != details::QUADRANGLE_VERTICES)
  {
    return false;
  }
  const size_t squaredSide1 = details::getSquaredDist(shape[0], shape[1]);
  const size_t squaredSide2 = details::getSquaredDist(shape[1], shape[2]);
  const size_t squaredSide3 = details::getSquaredDist(shape[2], shape[3]);
  const size_t squaredSide4 = details::getSquaredDist(shape[3], shape[0]);
  const size_t squaredDiagonal = details::getSquaredDist(shape[0], shape[2]);
  return ((squaredSide1 == squaredSide3) && (squaredSide2 == squaredSide4)
      && (squaredSide1 + squaredSide2 == squaredDiagonal));
}

bool isPentagon(const Shape &shape)
{
  return shape.size() == details::PENTAGON_VERTICES;
}

size_t details::getSquaredDist(const Point &point1, const Point &point2)
{
  const size_t distX = point2.x - point1.x;
  const size_t distY = point2.y - point1.y;
  return distX * distX + distY * distY;
}
