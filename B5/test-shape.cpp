#include <sstream>
#include <boost/test/unit_test.hpp>

#include "shape.hpp"

BOOST_AUTO_TEST_SUITE(shape)

struct Fixture
{
  std::istringstream input;
  std::ostringstream output;
  std::string rightOutput;
  Point point1;
  Point point2;
  Shape shape;
};

BOOST_FIXTURE_TEST_CASE(point_empty_input, Fixture)
{
  input.str("");
  input >> point1;
  BOOST_CHECK(input.fail());
}

BOOST_FIXTURE_TEST_CASE(point_first_number_invalid_input, Fixture)
{
  input.str("(a;5)");
  input >> point1;
  BOOST_CHECK(input.fail());
}

BOOST_FIXTURE_TEST_CASE(point_second_number_invalid_input, Fixture)
{
  input.str("(5;a)");
  input >> point1;
  BOOST_CHECK(input.fail());
}

BOOST_FIXTURE_TEST_CASE(point_both_number_invalidt_input, Fixture)
{
  input.str("(a;b)");
  input >> point1;
  BOOST_CHECK(input.fail());
}

BOOST_FIXTURE_TEST_CASE(point_no_opening_bracket_input, Fixture)
{
  input.str("1;2)");
  input >> point1;
  BOOST_CHECK(input.fail());
}

BOOST_FIXTURE_TEST_CASE(point_no_closing_bracket_input, Fixture)
{
  input.str("(1;2");
  input >> point1;
  BOOST_CHECK(input.fail());
}

BOOST_FIXTURE_TEST_CASE(point_no_delimeter_bracket_input, Fixture)
{
  input.str("(12)");
  input >> point1;
  BOOST_CHECK(input.fail());
}

BOOST_FIXTURE_TEST_CASE(point_wrong_delimeter_bracket_input, Fixture)
{
  input.str("(1.2)");
  input >> point1;
  BOOST_CHECK(input.fail());
}

BOOST_FIXTURE_TEST_CASE(point_valid_input, Fixture)
{
  input.str("(1;2)");
  input >> point1;
  BOOST_CHECK_EQUAL(point1.x, 1);
  BOOST_CHECK_EQUAL(point1.y, 2);
}

BOOST_FIXTURE_TEST_CASE(two_points_valid_input, Fixture)
{
  input.str("(1;2)\n(5;5)");
  input >> point1 >> point2;
  BOOST_CHECK_EQUAL(point1.x, 1);
  BOOST_CHECK_EQUAL(point1.y, 2);
  BOOST_CHECK_EQUAL(point2.x, 5);
  BOOST_CHECK_EQUAL(point2.y, 5);
}

BOOST_FIXTURE_TEST_CASE(point_output, Fixture)
{
  point1.x = 1;
  point1.y = 2;
  output << point1;
  rightOutput = "(1;2)";
  BOOST_CHECK_EQUAL(output.str(), rightOutput);
}

BOOST_FIXTURE_TEST_CASE(shape_empty_input, Fixture)
{
  input.str("");
  input >> shape;
  BOOST_CHECK(input.fail());
}

BOOST_FIXTURE_TEST_CASE(shape_invalid_point_input, Fixture)
{
  input.str("3 (1;1) (a;2) (3;1)");
  input >> shape;
  BOOST_CHECK(input.fail());
}

BOOST_FIXTURE_TEST_CASE(shape_too_few_points_input, Fixture)
{
  input.str("6 (1;2) (2;2) (3;1)");
  input >> shape;
  BOOST_CHECK(input.fail());
}

BOOST_FIXTURE_TEST_CASE(shape_valid_input, Fixture)
{
  input.str("3 (1;1) (2;2) (3;1)");
  input >> shape;
  BOOST_CHECK_EQUAL(shape.size(), 3);
  BOOST_CHECK_EQUAL(shape[0].x, 1);
  BOOST_CHECK_EQUAL(shape[0].y, 1);
  BOOST_CHECK_EQUAL(shape[1].x, 2);
  BOOST_CHECK_EQUAL(shape[1].y, 2);
  BOOST_CHECK_EQUAL(shape[2].x, 3);
  BOOST_CHECK_EQUAL(shape[2].y, 1);
}

BOOST_FIXTURE_TEST_CASE(shape_output, Fixture)
{
  shape.push_back({1, 1});
  shape.push_back({2, 2});
  shape.push_back({3, 1});
  rightOutput = "3 (1;1) (2;2) (3;1) ";
  output << shape;
  BOOST_CHECK_EQUAL(output.str(), rightOutput);
}

BOOST_FIXTURE_TEST_CASE(is_shape_triangle_check, Fixture)
{
  shape = {{1, 2}, {3, 4}, {2, 3}};
  BOOST_CHECK(isTriangle(shape));
  shape = {{1, 2}, {3, 4}, {5, 6}, {7, 8}};
  BOOST_CHECK(!isTriangle(shape));
}

BOOST_FIXTURE_TEST_CASE(is_shape_square_check, Fixture)
{
  shape = {{1, 1}, {1, 2}, {2, 2}, {2, 1}};
  BOOST_CHECK(isSquare(shape));
  shape = {{1, 1}, {1, 2}, {2, 3}, {2, 1}};
  BOOST_CHECK(!isSquare(shape));
}

BOOST_FIXTURE_TEST_CASE(is_shape_rectangles_check, Fixture)
{
  shape = {{1, 1}, {1, 2}, {3, 2}, {3, 1}};
  BOOST_CHECK(isRectangle(shape));
  shape = {{1, 1}, {1, 2}, {3, 4}, {3, -1}};
  BOOST_CHECK(!isRectangle(shape));
}

BOOST_FIXTURE_TEST_CASE(is_shape_pentagon_check, Fixture)
{
  shape = {{1, 2}, {3, 4}, {2, 3}, {5, 6}, {0, 0}};
  BOOST_CHECK(isPentagon(shape));
  shape = {{1, 2}, {3, 4}, {5, 6}, {7, 8}};
  BOOST_CHECK(!isPentagon(shape));
}

BOOST_AUTO_TEST_SUITE_END()
