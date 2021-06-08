#include <stdexcept>
#include <vector>
#include <forward_list>

#include <boost/test/unit_test.hpp>

#include "policy.hpp"
#include "utilities.hpp"
#include "tasks.hpp"

BOOST_AUTO_TEST_SUITE(details)

struct fixture
{
  fixture():
    testVector({6, 2, 8, 4, 2, 7, -2 }),
    testList({7, 4, 2, 9, 10 })
  {}

  std::vector<int> testVector;
  std::forward_list<int> testList;
};

BOOST_AUTO_TEST_CASE(test_get_comparator)
{
  const int largeInt = 10;
  const int smallInt = 2;
  std::function<bool(const int&, const int&)> compare = getComparator<int>("ascending");
  BOOST_CHECK_EQUAL(compare(smallInt, largeInt), false);
  compare = getComparator<int>("descending");
  BOOST_CHECK_EQUAL(compare(smallInt, largeInt), true);
  BOOST_CHECK_THROW(getComparator<int>("wrong order"), std::invalid_argument);
  BOOST_CHECK_THROW(getComparator<int>(nullptr), std::invalid_argument);
}

BOOST_FIXTURE_TEST_CASE(test_vector_index_sort, fixture)
{
  std::function<bool(const int&, const int&)> compare = getComparator<int>("ascending");
  std::vector<int> rightVector(testVector);
  std::vector<int> copyVector(testVector);

  std::sort(rightVector.begin(), rightVector.end(), std::less<int>());
  doBubbleSort<IndexPolicy>(testVector, compare);
  for (size_t i = 0; i < testVector.size(); i++)
  {
    BOOST_CHECK_EQUAL(testVector[i], rightVector[i]);
  }

  compare = getComparator<int>("descending");
  std::sort(rightVector.begin(), rightVector.end(), std::greater<int>());
  doBubbleSort<IndexPolicy>(copyVector, compare);
  for (size_t i = 0; i < copyVector.size(); i++)
  {
    BOOST_CHECK_EQUAL(copyVector[i], rightVector[i]);
  }
}

BOOST_FIXTURE_TEST_CASE(test_vector_at_sort, fixture)
{
  std::function<bool(const int&, const int&)> compare = getComparator<int>("ascending");
  std::vector<int> rightVector(testVector);
  std::vector<int> copyVector(testVector);

  std::sort(rightVector.begin(), rightVector.end(), std::less<int>());
  doBubbleSort<AtPolicy>(testVector, compare);
  for (size_t i = 0; i < testVector.size(); i++)
  {
    BOOST_CHECK_EQUAL(testVector[i], rightVector[i]);
  }

  compare = getComparator<int>("descending");
  std::sort(rightVector.begin(), rightVector.end(), std::greater<int>());
  doBubbleSort<AtPolicy>(copyVector, compare);
  for (size_t i = 0; i < copyVector.size(); i++)
  {
    BOOST_CHECK_EQUAL(copyVector[i], rightVector[i]);
  }
}

BOOST_FIXTURE_TEST_CASE(test_list_iterator_sort, fixture)
{
  std::function<bool(const int&, const int&)> compare = getComparator<int>("ascending");
  std::forward_list<int> rightList(testList);
  std::forward_list<int> copyList(testList);

  rightList.sort(std::less_equal<int>());
  doBubbleSort<IteratorPolicy>(testList, compare);
  std::forward_list<int>::iterator j = rightList.begin();
  for (std::forward_list<int>::iterator i = testList.begin(); i != testList.end(); i++, j++)
  {
    BOOST_CHECK_EQUAL(*i, *j);
  }

  compare = getComparator<int>("descending");
  rightList.sort(std::greater_equal<int>());
  doBubbleSort<IteratorPolicy>(copyList, compare);
  j = rightList.begin();
  for (std::forward_list<int>::iterator i = copyList.begin(); i != copyList.end(); i++, j++)
  {
    BOOST_CHECK_EQUAL(*i, *j);
  }
}

BOOST_AUTO_TEST_CASE(test_random_vector)
{
  const int vectorSize = 10;
  std::function<bool(const double&, const double&)> compare = getComparator<double>("ascending");
  std::vector<double> randomVector(vectorSize);
  fillRandom(randomVector.data(), vectorSize);
  std::vector<double> rightVector(randomVector);

  std::sort(rightVector.begin(), rightVector.end(), std::less<double>());
  doBubbleSort<IndexPolicy>(randomVector, compare);
  for (size_t i = 0; i < randomVector.size(); i++)
  {
    BOOST_CHECK_EQUAL(randomVector[i], rightVector[i]);
  }

  compare = getComparator<double>("descending");
  std::sort(rightVector.begin(), rightVector.end(), std::greater<double>());
  doBubbleSort<IndexPolicy>(randomVector, compare);
  for (size_t i = 0; i < randomVector.size(); i++)
  {
    BOOST_CHECK_EQUAL(randomVector[i], rightVector[i]);
  }
}

BOOST_AUTO_TEST_SUITE_END()
