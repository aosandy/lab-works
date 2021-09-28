#include <iostream>
#include <unordered_set>
#include <string>
#include <stdexcept>
#include <iterator>
#include <algorithm>
#include <list>
#include <sstream>
#include <numeric>

#include "shape.hpp"

void doTask1(std::istream&, std::ostream&);
void doTask2(std::istream &input, std::ostream &output);

int main(int argc, char* args[])
{
  const int validArgc = 2;
  if (argc != validArgc)
  {
    std::cerr << "Wrong arguments number\n";
    return 1;
  }
  int number = 0;
  std::istringstream numberStream(args[1]);
  numberStream >> number;
  if (!(numberStream.eof()) || (number < 1) || (number > 2))
  {
    std::cerr << "Wrong number of task\n";
    return 1;
  }
  try
  {
    if (number == 1)
    {
      doTask1(std::cin, std::cout);
    }
    else if (number == 2)
    {
      doTask2(std::cin, std::cout);
    }
  }
  catch (const std::exception &e)
  {
    std::cerr << e.what() << '\n';
    return 2;
  }
  return 0;
}

void doTask1(std::istream &input, std::ostream &output)
{
  std::unordered_set<std::string> set((std::istream_iterator<std::string>(input)),
      std::istream_iterator<std::string>());
  if (!input.eof())
  {
    throw std::runtime_error("Invalid input");
  }
  std::copy(set.begin(), set.end(), std::ostream_iterator<std::string>(output, "\n"));
}

void doTask2(std::istream &input, std::ostream &output)
{
  std::list<Shape> shapes((std::istream_iterator<Shape>(input)), std::istream_iterator<Shape>());
  if (!input.eof())
  {
    throw std::runtime_error("Invalid input");
  }

  const size_t vertices = std::accumulate(shapes.begin(), shapes.end(), 0,
      [](const size_t init, const Shape& shape)
      {
        return init + shape.size();
      });

  const size_t triangles = std::count_if(shapes.begin(), shapes.end(), &isTriangle);
  const size_t squares = std::count_if(shapes.begin(), shapes.end(), &isSquare);
  const size_t rectangles = std::count_if(shapes.begin(), shapes.end(), &isRectangle);

  shapes.erase(std::remove_if(shapes.begin(), shapes.end(), &isPentagon), shapes.end());

  std::vector<Point> points(shapes.size());
  std::transform(shapes.begin(), shapes.end(), points.begin(),
      [](const Shape &shape)
      {
        return shape[0];
      });

  shapes.sort(ShapesComparator());

  output << "Vertices: " << vertices << "\nTriangles: " << triangles << "\nSquares: " << squares
      << "\nRectangles: " << rectangles << "\nPoints: ";
  std::copy(points.begin(), points.end(), std::ostream_iterator<Point>(output, " "));
  output << "\nShapes:\n";
  std::copy(shapes.begin(), shapes.end(), std::ostream_iterator<Shape>(output, "\n"));
}
