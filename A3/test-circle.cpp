#define _USE_MATH_DEFINES
#include <cmath>
#include <stdexcept>

#include <boost/test/unit_test.hpp>
#include "circle.hpp"

BOOST_AUTO_TEST_SUITE(circle)

using namespace peskov;

const double EPSILON = 0.0001;
const double RADIUS = 2.8;
const double INVALID_RADIUS1 = -12.62;
const double INVALID_RADIUS2 = 0.0;
const double COEFFICIENT = 2.534;
const double INVALID_COEFFICIENT1 = -0.98;
const double INVALID_COEFFICIENT2 = 0.0;
const point_t POS = { 8.4, 4.23 };
const point_t NEW_POS = { -3.6, 0.78 };
const double DX = -0.34;
const double DY = 7.5;

BOOST_AUTO_TEST_CASE(are_parameters_const_when_moving_in_point)
{
  Circle testCircle(POS, RADIUS);
  const rectangle_t testFrame = testCircle.getFrameRect();
  const double area = testCircle.getArea();
  testCircle.move(NEW_POS);
  const rectangle_t newFrame = testCircle.getFrameRect();
  BOOST_CHECK_CLOSE(testFrame.width, newFrame.width, EPSILON);
  BOOST_CHECK_CLOSE(testFrame.height, newFrame.height, EPSILON);
  BOOST_CHECK_CLOSE(area, testCircle.getArea(), EPSILON);
}

BOOST_AUTO_TEST_CASE(are_parameters_const_when_moving_dx_dy)
{
  Circle testCircle(POS, RADIUS);
  const rectangle_t testFrame = testCircle.getFrameRect();
  const double area = testCircle.getArea();
  testCircle.move(DX, DY);
  const rectangle_t newFrame = testCircle.getFrameRect();
  BOOST_CHECK_CLOSE(testFrame.width, newFrame.width, EPSILON);
  BOOST_CHECK_CLOSE(testFrame.height, newFrame.height, EPSILON);
  BOOST_CHECK_CLOSE(area, testCircle.getArea(), EPSILON);
}

BOOST_AUTO_TEST_CASE(quadratic_change_in_area_when_scaling)
{
  Circle testCircle(POS, RADIUS);
  const double area = testCircle.getArea();
  testCircle.scale(COEFFICIENT);
  BOOST_CHECK_CLOSE(area * COEFFICIENT * COEFFICIENT, testCircle.getArea(), EPSILON);
}

BOOST_AUTO_TEST_CASE(constructor_arguments_are_not_positive)
{
  BOOST_CHECK_THROW(Circle(POS, INVALID_RADIUS1), std::invalid_argument);
  BOOST_CHECK_THROW(Circle(POS, INVALID_RADIUS2), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(scale_arguments_are_not_positive)
{
  Circle testCircle(POS, RADIUS);
  BOOST_CHECK_THROW(testCircle.scale(INVALID_COEFFICIENT1), std::invalid_argument);
  BOOST_CHECK_THROW(testCircle.scale(INVALID_COEFFICIENT2), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_get_area)
{
  Circle testCircle(POS, RADIUS);
  const double area = RADIUS * RADIUS * M_PI;
  BOOST_CHECK_CLOSE(area, testCircle.getArea(), EPSILON);
}

BOOST_AUTO_TEST_CASE(test_get_frame_rect)
{
  Circle testCircle(POS, RADIUS);
  const double width = RADIUS * 2;
  const double height = RADIUS * 2;
  BOOST_CHECK_CLOSE(width, testCircle.getFrameRect().width, EPSILON);
  BOOST_CHECK_CLOSE(height, testCircle.getFrameRect().height, EPSILON);
}

BOOST_AUTO_TEST_SUITE_END()
