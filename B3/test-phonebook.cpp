#include <boost/test/unit_test.hpp>
#include <string>

#include "phonebook.hpp"

BOOST_AUTO_TEST_SUITE(test_phonebook)

struct Fixture
{
  Fixture()
  {
    phonebook.pushBack({name1, number1});
    phonebook.pushBack({name2, number2});
    phonebook.pushBack({name3, number3});
    firstPlace = phonebook.begin();
    lastPlace = std::prev(phonebook.end());
  }
  Phonebook phonebook;
  Phonebook::iterator firstPlace;
  Phonebook::iterator lastPlace;

  const std::string number1 = "88005553535";
  const std::string name1 = "Ivan";
  const std::string number2 = "123456789";
  const std::string name2 = "Alexander";
  const std::string number3 = "555";
  const std::string name3 = "abcd";
  const std::string newNumber = "777777777";
  const std::string newName = "new name";
};

BOOST_FIXTURE_TEST_CASE(test_replace, Fixture)
{
  phonebook.replace(firstPlace, {name3, number3});
  BOOST_CHECK_EQUAL(firstPlace->number, number3);
  BOOST_CHECK_EQUAL(firstPlace->name, name3);
  phonebook.replace(lastPlace, {name1, number1});
  BOOST_CHECK_EQUAL(lastPlace->number, number1);
  BOOST_CHECK_EQUAL(lastPlace->name, name1);
}

BOOST_FIXTURE_TEST_CASE(test_erase, Fixture)
{
  phonebook.erase(lastPlace--);
  BOOST_CHECK_EQUAL(lastPlace->number, number2);
  BOOST_CHECK_EQUAL(lastPlace->name, name2);
  phonebook.erase(firstPlace++);
  BOOST_CHECK_EQUAL(firstPlace->number, number2);
  BOOST_CHECK_EQUAL(firstPlace->name, name2);
}

BOOST_FIXTURE_TEST_CASE(test_insert, Fixture)
{
  phonebook.insertBefore(firstPlace, {newName, newNumber});
  phonebook.insertAfter(firstPlace, {newName, newNumber});
  phonebook.insertBefore(lastPlace, {newName, newNumber});
  phonebook.insertAfter(lastPlace, {newName, newNumber});
  firstPlace = phonebook.begin();
  lastPlace = std::prev(phonebook.end());
  BOOST_CHECK_EQUAL(firstPlace->number, lastPlace->number);
  BOOST_CHECK_EQUAL(firstPlace->name, lastPlace->name);
}

BOOST_FIXTURE_TEST_CASE(test_push_back, Fixture)
{
  phonebook.pushBack({newName, newNumber});
  phonebook.pushBack({newName, newNumber});
  auto newLastPlace = std::prev(phonebook.end());
  BOOST_CHECK_EQUAL(newLastPlace->number, std::prev(newLastPlace)->number);
  BOOST_CHECK_EQUAL(newLastPlace->name, std::prev(newLastPlace)->name);
}

BOOST_FIXTURE_TEST_CASE(test_empty, Fixture)
{
  Phonebook phonebook;
  BOOST_CHECK_EQUAL(phonebook.isEmpty(), true);
  phonebook.pushBack({newName, newNumber});
  BOOST_CHECK_EQUAL(phonebook.isEmpty(), false);
}

BOOST_AUTO_TEST_SUITE_END()
