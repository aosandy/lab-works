#include <sstream>

#include <boost/test/unit_test.hpp>

#include "data_struct.hpp"

BOOST_AUTO_TEST_SUITE(data_struct)

struct Fixture
{
  DataStruct dataStruct;
  std::istringstream input;
  std::ostringstream output;
};

BOOST_AUTO_TEST_CASE(comparison)
{
  DataStructsComparator comparator;
  DataStruct dataStruct1 = {1, 1, "a"};
  DataStruct dataStruct2 = {1, 1, "a"};
  BOOST_CHECK(!comparator(dataStruct1, dataStruct2));
  dataStruct2 = {1, 1, "aa"};
  BOOST_CHECK(comparator(dataStruct1, dataStruct2));
  dataStruct1 = {1, 1, "a"};
  dataStruct2 = {1, 5, "a"};
  BOOST_CHECK(comparator(dataStruct1, dataStruct2));
}

BOOST_FIXTURE_TEST_CASE(input_test, Fixture)
{
  input.str("1,4,a");
  input >> dataStruct;
  BOOST_CHECK(dataStruct.key1 == 1);
  BOOST_CHECK(dataStruct.key2 == 4);
  BOOST_CHECK(dataStruct.str == "a");

  input.str("b,0,bb");
  input >> dataStruct;
  BOOST_CHECK(!input);
  input.clear();

  input.str("0,0   aaa");
  input >> dataStruct;
  BOOST_CHECK(!input);
  input.clear();

  input.str("6,1,bb");
  input >> dataStruct;
  BOOST_CHECK(!input);
  input.clear();

  input.str("1, 1.8, w");
  input >> dataStruct;
  BOOST_CHECK(!input);
  input.clear();
}

BOOST_FIXTURE_TEST_CASE(output_test, Fixture)
{
  dataStruct = {1, 1, "word"};
  output << dataStruct;
  BOOST_CHECK_EQUAL(output.str(), "1,1,word");
}

BOOST_AUTO_TEST_SUITE_END()
