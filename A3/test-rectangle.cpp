#include <stdexcept>

#include <boost/test/unit_test.hpp>
#include "rectangle.hpp"

BOOST_AUTO_TEST_SUITE(rectangle)

using namespace peskov;

const double EPSILON = 0.0001;
const double WIDTH = 10.5;
const double HEIGHT = 4.87;
const double INVALID_WIDTH = -7.54;
const double INVALID_HEIGHT = 0.0;
const double COEFFICIENT = 0.5;
const double INVALID_COEFFICIENT1 = -5;
const double INVALID_COEFFICIENT2 = 0.0;
const point_t POS = { 6.7, 3.64 };
const point_t NEW_POS = { 0.0, -8.9 };
const double DX = 5.5;
const double DY = 23.4345;

BOOST_AUTO_TEST_CASE(are_parameters_const_when_moving_in_point)
{
  Rectangle testRectangle(POS, WIDTH, HEIGHT);
  const rectangle_t testFrame = testRectangle.getFrameRect();
  const double area = testRectangle.getArea();
  testRectangle.move(NEW_POS);
  const rectangle_t newFrame = testRectangle.getFrameRect();
  BOOST_CHECK_CLOSE(testFrame.width, newFrame.width, EPSILON);
  BOOST_CHECK_CLOSE(testFrame.height, newFrame.height, EPSILON);
  BOOST_CHECK_CLOSE(area, testRectangle.getArea(), EPSILON);
}

BOOST_AUTO_TEST_CASE(are_parameters_const_when_moving_dx_dy)
{
  Rectangle testRectangle(POS, WIDTH, HEIGHT);
  const rectangle_t testFrame = testRectangle.getFrameRect();
  const double area = testRectangle.getArea();
  testRectangle.move(DX, DY);
  const rectangle_t newFrame = testRectangle.getFrameRect();
  BOOST_CHECK_CLOSE(testFrame.width, newFrame.width, EPSILON);
  BOOST_CHECK_CLOSE(testFrame.height, newFrame.height, EPSILON);
  BOOST_CHECK_CLOSE(area, testRectangle.getArea(), EPSILON);
}

BOOST_AUTO_TEST_CASE(quadratic_change_in_area_when_scaling)
{
  Rectangle testRectangle(POS, WIDTH, HEIGHT);
  const double area = testRectangle.getArea();
  testRectangle.scale(COEFFICIENT);
  BOOST_CHECK_CLOSE(area * COEFFICIENT * COEFFICIENT, testRectangle.getArea(), EPSILON);
}

BOOST_AUTO_TEST_CASE(constructor_arguments_are_not_positive)
{
  BOOST_CHECK_THROW(Rectangle(POS, INVALID_WIDTH, INVALID_HEIGHT), std::invalid_argument);
  BOOST_CHECK_THROW(Rectangle(POS, INVALID_WIDTH, HEIGHT), std::invalid_argument);
  BOOST_CHECK_THROW(Rectangle(POS, WIDTH, INVALID_HEIGHT), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(scale_arguments_are_not_positive)
{
  Rectangle testRectangle(POS, WIDTH, HEIGHT);
  BOOST_CHECK_THROW(testRectangle.scale(INVALID_COEFFICIENT1), std::invalid_argument);
  BOOST_CHECK_THROW(testRectangle.scale(INVALID_COEFFICIENT2), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_get_area)
{
  Rectangle testRectangle(POS, WIDTH, HEIGHT);
  const double area = WIDTH * HEIGHT;
  BOOST_CHECK_CLOSE(area, testRectangle.getArea(), EPSILON);
}

BOOST_AUTO_TEST_CASE(test_get_frame_rect)
{
  Rectangle testRectangle(POS, WIDTH, HEIGHT);
  BOOST_CHECK_CLOSE(WIDTH, testRectangle.getFrameRect().width, EPSILON);
  BOOST_CHECK_CLOSE(HEIGHT, testRectangle.getFrameRect().height, EPSILON);
}

BOOST_AUTO_TEST_SUITE_END()
