#include <stdexcept>

#include <boost/test/unit_test.hpp>

#include "tasks.hpp"

BOOST_AUTO_TEST_SUITE(tasks)

BOOST_AUTO_TEST_CASE(invalid_order)
{
  BOOST_CHECK_THROW(doTask1(nullptr), std::invalid_argument);
  BOOST_CHECK_THROW(doTask1("wrong order"), std::invalid_argument);

  BOOST_CHECK_THROW(doTask4(nullptr, 5), std::invalid_argument);
  BOOST_CHECK_THROW(doTask4("wrong order", 5), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(invalid_file_name)
{
  BOOST_CHECK_THROW(doTask2(nullptr), std::invalid_argument);
  BOOST_CHECK_THROW(doTask2("wrong name"), std::runtime_error);
}

BOOST_AUTO_TEST_SUITE_END()
