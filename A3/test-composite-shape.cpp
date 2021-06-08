#include <memory>
#include <stdexcept>

#include <boost/test/unit_test.hpp>
#include "composite-shape.hpp"
#include "base-types.hpp"
#include "rectangle.hpp"
#include "circle.hpp"

BOOST_AUTO_TEST_SUITE(composite_shape)

using namespace peskov;

const double EPSILON = 0.0001;
const double RADIUS = 2.8;
const double WIDTH = 10.5;
const double HEIGHT = 4.87;
const double DEC_COEFF = 0.67;
const double INC_COEFF = 1.23;
const double INVALID_COEFFICIENT1 = -1.5;
const double INVALID_COEFFICIENT2 = 0.0;
const point_t POS1 = { 5.6, 4.2 };
const point_t POS2 = { -3.54, 56.3 };
const point_t NEW_POS = { -5.4, 2.32 };
const double DX = 9.43;
const double DY = 7;

struct fixture
{
  CompositeShape testCompShape;
  Shape::Ptr testCircle = std::make_shared<Circle>(POS1, RADIUS);
  Shape::Ptr testRectangle = std::make_shared<Rectangle>(POS2, WIDTH, HEIGHT);
  fixture()
  {
    testCompShape.add(testCircle);
    testCompShape.add(testRectangle);
  }
};

BOOST_FIXTURE_TEST_CASE(moving_in_point, fixture)
{
  const rectangle_t oldFrame = testCompShape.getFrameRect();
  const double area = testCompShape.getArea();
  testCompShape.move(NEW_POS);
  const rectangle_t newFrame = testCompShape.getFrameRect();
  BOOST_CHECK_CLOSE(oldFrame.width, newFrame.width, EPSILON);
  BOOST_CHECK_CLOSE(oldFrame.height, newFrame.height, EPSILON);
  BOOST_CHECK_CLOSE(newFrame.pos.x, NEW_POS.x, EPSILON);
  BOOST_CHECK_CLOSE(newFrame.pos.y, NEW_POS.y, EPSILON);
  BOOST_CHECK_CLOSE(area, testCompShape.getArea(), EPSILON);
}

BOOST_FIXTURE_TEST_CASE(moving_dx_dy, fixture)
{
  const rectangle_t oldFrame = testCompShape.getFrameRect();
  const double area = testCompShape.getArea();
  testCompShape.move(DX, DY);
  const rectangle_t newFrame = testCompShape.getFrameRect();
  BOOST_CHECK_CLOSE(oldFrame.width, newFrame.width, EPSILON);
  BOOST_CHECK_CLOSE(oldFrame.height, newFrame.height, EPSILON);
  BOOST_CHECK_CLOSE(newFrame.pos.x, oldFrame.pos.x + DX, EPSILON);
  BOOST_CHECK_CLOSE(newFrame.pos.y, oldFrame.pos.y + DY, EPSILON);
  BOOST_CHECK_CLOSE(area, testCompShape.getArea(), EPSILON);
}

BOOST_FIXTURE_TEST_CASE(test_decreasing_scaling, fixture)
{
  const size_t size = testCompShape.getSize();
  const double area = testCompShape.getArea();
  const rectangle_t oldFrame = testCompShape.getFrameRect();
  const point_t oldPos = oldFrame.pos;
  point_t *shapesPos = new point_t[size];
  for (size_t i = 0; i < size; i++)
  {
    shapesPos[i] = testCompShape[i]->getFrameRect().pos;
  }
  testCompShape.scale(DEC_COEFF);
  const rectangle_t newFrame = testCompShape.getFrameRect();
  const point_t newPos = newFrame.pos;
  BOOST_CHECK_EQUAL(size, testCompShape.getSize());
  BOOST_CHECK_CLOSE(area * DEC_COEFF * DEC_COEFF, testCompShape.getArea(), EPSILON);
  BOOST_CHECK_CLOSE(oldPos.x, newPos.x, EPSILON);
  BOOST_CHECK_CLOSE(oldPos.y, newPos.y, EPSILON);
  BOOST_CHECK_CLOSE(oldFrame.width * DEC_COEFF, newFrame.width, EPSILON);
  BOOST_CHECK_CLOSE(oldFrame.height * DEC_COEFF, newFrame.height, EPSILON);
  double newX, newY;
  for (size_t i = 0; i < size; i++)
  {
    newX = newPos.x + ((shapesPos[i].x - newPos.x) * DEC_COEFF);
    newY = newPos.y + ((shapesPos[i].y - newPos.y) * DEC_COEFF);
    BOOST_CHECK_CLOSE(testCompShape[i]->getFrameRect().pos.x, newX, EPSILON);
    BOOST_CHECK_CLOSE(testCompShape[i]->getFrameRect().pos.y, newY, EPSILON);
  }
  delete[] shapesPos;
}

BOOST_FIXTURE_TEST_CASE(test_increasing_scaling, fixture)
{
  const size_t size = testCompShape.getSize();
  const double area = testCompShape.getArea();
  const rectangle_t oldFrame = testCompShape.getFrameRect();
  const point_t oldPos = oldFrame.pos;
  point_t *shapesPos = new point_t[size];
  for (size_t i = 0; i < size; i++)
  {
    shapesPos[i] = testCompShape[i]->getFrameRect().pos;
  }
  testCompShape.scale(INC_COEFF);
  const rectangle_t newFrame = testCompShape.getFrameRect();
  const point_t newPos = newFrame.pos;
  BOOST_CHECK_EQUAL(size, testCompShape.getSize());
  BOOST_CHECK_CLOSE(area * INC_COEFF * INC_COEFF, testCompShape.getArea(), EPSILON);
  BOOST_CHECK_CLOSE(oldPos.x, newPos.x, EPSILON);
  BOOST_CHECK_CLOSE(oldPos.y, newPos.y, EPSILON);
  BOOST_CHECK_CLOSE(oldFrame.width * INC_COEFF, newFrame.width, EPSILON);
  BOOST_CHECK_CLOSE(oldFrame.height * INC_COEFF, newFrame.height, EPSILON);
  double newX, newY;
  for (size_t i = 0; i < size; i++)
  {
    newX = newPos.x + ((shapesPos[i].x - newPos.x) * INC_COEFF);
    newY = newPos.y + ((shapesPos[i].y - newPos.y) * INC_COEFF);
    BOOST_CHECK_CLOSE(testCompShape[i]->getFrameRect().pos.x, newX, EPSILON);
    BOOST_CHECK_CLOSE(testCompShape[i]->getFrameRect().pos.y, newY, EPSILON);
  }
  delete[] shapesPos;
}

BOOST_FIXTURE_TEST_CASE(scale_coefficient_is_not_positive, fixture)
{
  BOOST_CHECK_THROW(testCompShape.scale(INVALID_COEFFICIENT1), std::invalid_argument);
  BOOST_CHECK_THROW(testCompShape.scale(INVALID_COEFFICIENT2), std::invalid_argument);
}

BOOST_FIXTURE_TEST_CASE(index_out_of_range, fixture)
{
  BOOST_CHECK_THROW(testCompShape[2], std::out_of_range);
}

BOOST_FIXTURE_TEST_CASE(add_nullptr, fixture)
{
  BOOST_CHECK_THROW(testCompShape.add(nullptr), std::invalid_argument);
}

BOOST_FIXTURE_TEST_CASE(add_shape_to_itself, fixture)
{
  std::shared_ptr<CompositeShape> compShapePtr(std::make_shared<CompositeShape>(testCompShape));
  BOOST_CHECK_THROW(compShapePtr->add(compShapePtr), std::invalid_argument);
}

BOOST_FIXTURE_TEST_CASE(add_shape_that_already_contained, fixture)
{
  BOOST_CHECK_THROW(testCompShape.add(testCircle), std::invalid_argument);
}

BOOST_FIXTURE_TEST_CASE(copy_constructor, fixture)
{
  CompositeShape copyCompShape(testCompShape);
  rectangle_t testFrame1 = testCompShape.getFrameRect();
  rectangle_t testFrame2 = copyCompShape.getFrameRect();
  BOOST_CHECK_CLOSE(testFrame1.pos.x, testFrame2.pos.x, EPSILON);
  BOOST_CHECK_CLOSE(testFrame1.pos.y, testFrame2.pos.y, EPSILON);
  BOOST_CHECK_CLOSE(testCompShape.getArea(), copyCompShape.getArea(), EPSILON);
  BOOST_CHECK_CLOSE(testFrame1.width, testFrame2.width, EPSILON);
  BOOST_CHECK_CLOSE(testFrame1.height, testFrame2.height, EPSILON);
  BOOST_CHECK_EQUAL(testCompShape.getSize(), copyCompShape.getSize());
  for (size_t i = 0; i < testCompShape.getSize(); i++)
  {
    BOOST_CHECK_EQUAL(testCompShape[i], copyCompShape[i]);
  }
}

BOOST_FIXTURE_TEST_CASE(move_constructor, fixture)
{
  CompositeShape copyCompShape(testCompShape);
  CompositeShape movedCompShape(std::move(testCompShape));
  BOOST_CHECK_EQUAL(testCompShape.getSize(), 0);
  BOOST_CHECK_THROW(testCompShape[0], std::out_of_range);
  BOOST_CHECK_EQUAL(movedCompShape.getSize(), copyCompShape.getSize());
  for (size_t i = 0; i < movedCompShape.getSize(); i++)
  {
    BOOST_CHECK_EQUAL(movedCompShape[i], copyCompShape[i]);
  }
}

BOOST_FIXTURE_TEST_CASE(copy_operator, fixture)
{
  BOOST_CHECK_NO_THROW(CompositeShape copyCompShape = testCompShape);
  CompositeShape copyCompShape(testCompShape);
  rectangle_t testFrame1 = testCompShape.getFrameRect();
  rectangle_t testFrame2 = copyCompShape.getFrameRect();
  BOOST_CHECK_CLOSE(testFrame1.pos.x, testFrame2.pos.x, EPSILON);
  BOOST_CHECK_CLOSE(testFrame1.pos.y, testFrame2.pos.y, EPSILON);
  BOOST_CHECK_CLOSE(testCompShape.getArea(), copyCompShape.getArea(), EPSILON);
  BOOST_CHECK_CLOSE(testFrame1.width, testFrame2.width, EPSILON);
  BOOST_CHECK_CLOSE(testFrame1.height, testFrame2.height, EPSILON);
  BOOST_CHECK_EQUAL(testCompShape.getSize(), copyCompShape.getSize());
  for (size_t i = 0; i < testCompShape.getSize(); i++)
  {
    BOOST_CHECK_EQUAL(testCompShape[i], copyCompShape[i]);
  }
}

BOOST_FIXTURE_TEST_CASE(self_copy, fixture)
{
  testCompShape = testCompShape;
  BOOST_CHECK_EQUAL(testCompShape[0], testCircle);
  BOOST_CHECK_EQUAL(testCompShape[1], testRectangle);
}

BOOST_FIXTURE_TEST_CASE(move_operator, fixture)
{
  BOOST_CHECK_NO_THROW(CompositeShape newCompShape = std::move(testCompShape));
  CompositeShape newCompShape(testCompShape);
  BOOST_CHECK_EQUAL(testCompShape.getSize(), 0);
  BOOST_CHECK_THROW(testCompShape[0], std::out_of_range);
}

BOOST_AUTO_TEST_CASE(methods_of_empty_shape)
{
  CompositeShape emptyCompShape;
  BOOST_CHECK_THROW(emptyCompShape[0], std::out_of_range);
  BOOST_CHECK_THROW(emptyCompShape.getFrameRect(), std::length_error);
  BOOST_CHECK_THROW(emptyCompShape.move(NEW_POS), std::length_error);
  BOOST_CHECK_THROW(emptyCompShape.move(DX, DY), std::length_error);
  BOOST_CHECK_THROW(emptyCompShape.scale(INC_COEFF), std::length_error);
  BOOST_CHECK_THROW(emptyCompShape.remove(0), std::length_error);
  BOOST_CHECK_EQUAL(emptyCompShape.getSize(), 0);
}

BOOST_FIXTURE_TEST_CASE(get_shapes, fixture)
{
  Shape::Ptr gotCircle = testCompShape[0];
  Shape::Ptr gotRectangle = testCompShape[1];
  BOOST_CHECK_EQUAL(testCircle, gotCircle);
  BOOST_CHECK_EQUAL(testRectangle, gotRectangle);
}

BOOST_FIXTURE_TEST_CASE(test_removing_from_last, fixture)
{
  const size_t originSize = testCompShape.getSize();
  const size_t indexLast = originSize - 1;
  for (size_t i = indexLast; i < originSize; i--)
  {
    Shape::Ptr deletingShape = testCompShape[i];
    testCompShape.remove(i);
    BOOST_CHECK_THROW(testCompShape[i], std::out_of_range);
    BOOST_CHECK_EQUAL(i, testCompShape.getSize());
    for (size_t j = 0; j < testCompShape.getSize(); j++)
    {
      BOOST_CHECK(deletingShape != testCompShape[j]);
    }
  }
}

BOOST_FIXTURE_TEST_CASE(test_removing_from_first, fixture)
{
  const size_t originSize = testCompShape.getSize();
  const size_t indexLast = originSize - 1;
  for (size_t i = 0; i < originSize; i++)
  {
    Shape::Ptr deletingShape = testCompShape[0];
    testCompShape.remove(0);
    BOOST_CHECK_THROW(testCompShape[indexLast - i], std::out_of_range);
    BOOST_CHECK_EQUAL(indexLast - i, testCompShape.getSize());
    for (size_t j = 0; j < testCompShape.getSize(); j++)
    {
      BOOST_CHECK(deletingShape != testCompShape[j]);
    }
  }
}

BOOST_FIXTURE_TEST_CASE(test_get_size, fixture)
{
  BOOST_CHECK_EQUAL(testCompShape.getSize(), 2);
}

BOOST_FIXTURE_TEST_CASE(test_get_area, fixture)
{
  double area = 0.0;
  for (size_t i = 0; i < testCompShape.getSize(); i++)
  {
    area += testCompShape[i]->getArea();
  }
  BOOST_CHECK_CLOSE(testCompShape.getArea(), area, EPSILON);
}

BOOST_FIXTURE_TEST_CASE(test_get_frame_rect, fixture)
{
  BOOST_CHECK_NO_THROW(testCompShape[0]);
  rectangle_t rect = testCompShape[0]->getFrameRect();
  double posX = rect.pos.x;
  double posY = rect.pos.y;
  double halfWidth = rect.width / 2.0;
  double halfHeight = rect.width / 2.0;

  double minX = posX - halfWidth;
  double maxX = posX + halfWidth;
  double minY = posY - halfHeight;
  double maxY = posY + halfHeight;
  for (size_t i = 1; i < testCompShape.getSize(); i++)
  {
    rect = testCompShape[i]->getFrameRect();
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
  rectangle_t correctFrame = { maxX - minX, maxY - minY, pos};

  rectangle_t testFrame = testCompShape.getFrameRect();
  BOOST_CHECK_CLOSE(correctFrame.width, testFrame.width, EPSILON);
  BOOST_CHECK_CLOSE(correctFrame.height, testFrame.height, EPSILON);
  BOOST_CHECK_CLOSE(correctFrame.pos.x, testFrame.pos.x, EPSILON);
  BOOST_CHECK_CLOSE(correctFrame.pos.y, testFrame.pos.y, EPSILON);
}

BOOST_AUTO_TEST_SUITE_END()
