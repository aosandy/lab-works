#include <boost/test/unit_test.hpp>

#include "factorial_container.hpp"

BOOST_AUTO_TEST_SUITE(factorial_container)

BOOST_AUTO_TEST_CASE(test_iterators)
{
  FactorialContainer factorialContainer(10);
  size_t factorial = 1;
  size_t number = 1;
  for (const_iterator it = factorialContainer.begin(); it != factorialContainer.end(); ++it, ++number)
  {
    factorial *= number;
    BOOST_CHECK_EQUAL(factorial, *it);
  }
  number = 10;
  for (FactorialContainer::const_reverse_iterator it = factorialContainer.rbegin();
       it != factorialContainer.rend(); ++it, --number)
  {
    BOOST_CHECK_EQUAL(factorial, *it);
    factorial /= number;
  }
}

BOOST_AUTO_TEST_CASE(test_empty)
{
  FactorialContainer emptyContainer(0);
  BOOST_CHECK_THROW(--emptyContainer.begin(), std::out_of_range);
  BOOST_CHECK_THROW(++emptyContainer.begin(), std::out_of_range);
  BOOST_CHECK_THROW(--emptyContainer.rbegin(), std::out_of_range);
  BOOST_CHECK_THROW(++emptyContainer.rbegin(), std::out_of_range);
  BOOST_CHECK_THROW(--emptyContainer.end(), std::out_of_range);
  BOOST_CHECK_THROW(++emptyContainer.rend(), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(test_overflow)
{
  BOOST_CHECK_THROW(FactorialContainer overflowContainer(30);, std::overflow_error);
}

BOOST_AUTO_TEST_SUITE_END()
