#include <boost/test/unit_test.hpp>
#include <string>
#include <sstream>

#include "phonebook_interface.hpp"

BOOST_AUTO_TEST_SUITE(test_phonebook_interface)

struct Fixture
{
  Fixture()
  {
    interface.add(record1, out);
    interface.add(record2, out);
    interface.add(record3, out);
    interface.move("current", stepsFirst, out);
  }
  PhonebookInterface interface;
  PhonebookInterface interfaceEmpty;

  std::ostringstream out;
  std::ostringstream rightOut;
  const std::string number1 = "88005553535";
  const std::string name1 = "Ivan";
  const std::string number2 = "123456789";
  const std::string name2 = "Alexander";
  const std::string number3 = "555";
  const std::string name3 = "abcd";
  const std::string newNumber = "777777777";
  const std::string newName = "new name";
  Phonebook::record_t record1 = {name1, number1};
  Phonebook::record_t record2 = {name2, number2};
  Phonebook::record_t record3 = {name3, number3};
  Phonebook::record_t newRecord = {newName, newNumber};
  const PhonebookInterface::steps_t stepsLast = {PhonebookInterface::LAST,
      PhonebookInterface::KEYWORD};
  const PhonebookInterface::steps_t stepsFirst = {PhonebookInterface::FIRST,
      PhonebookInterface::KEYWORD};
  const PhonebookInterface::steps_t stepForward = {.steps = 1, .storedType = PhonebookInterface::NUMERIC};
  const PhonebookInterface::steps_t stepBackward = {.steps = -1, .storedType = PhonebookInterface::NUMERIC};
  const PhonebookInterface::steps_t stepsInvalid = {.storedType = PhonebookInterface::INVALID};
  const std::string INVALID_BOOKMARK = "<INVALID BOOKMARK>\n";
  const std::string EMPTY = "<EMPTY>\n";
  const std::string INVALID_STEP = "<INVALID STEP>\n";
};

BOOST_FIXTURE_TEST_CASE(test_add, Fixture)
{
  interface.add(newRecord, out);
  interface.move("current", stepsLast, out);
  interface.show("current", out);
  rightOut << newNumber << ' '  << newName << '\n';
  BOOST_CHECK_EQUAL(out.str(), rightOut.str());
}

BOOST_FIXTURE_TEST_CASE(test_add_empty, Fixture)
{
  interfaceEmpty.add(newRecord, out);
  interfaceEmpty.show("current", out);
  rightOut << newNumber << ' '  << newName << '\n';
  BOOST_CHECK_EQUAL(out.str(), rightOut.str());
}

BOOST_FIXTURE_TEST_CASE(test_store, Fixture)
{
  interface.store("current", "first", out);
  interface.move("current", stepsLast, out);
  interface.store("current", "last", out);
  interface.show("first", out);
  interface.show("last", out);
  rightOut << number1 << ' ' << name1 << '\n'
           << number3 << ' ' << name3 << '\n';
  BOOST_CHECK_EQUAL(out.str(), rightOut.str());
}

BOOST_FIXTURE_TEST_CASE(test_store_nonexistent_mark, Fixture)
{
  interface.store("nonexistent mark", "first", out);
  rightOut << INVALID_BOOKMARK;
  BOOST_CHECK_EQUAL(out.str(), rightOut.str());
}

BOOST_FIXTURE_TEST_CASE(test_insert, Fixture)
{
  interface.insert(PhonebookInterface::BEFORE, "current", newRecord, out);
  interface.insert(PhonebookInterface::AFTER, "current", newRecord, out);
  interface.move("current", stepsLast, out);
  interface.insert(PhonebookInterface::BEFORE, "current", newRecord, out);
  interface.insert(PhonebookInterface::AFTER, "current", newRecord, out);
  interface.move("current", stepsFirst, out);
  interface.show("current", out);
  interface.move("current", stepsLast, out);
  interface.show("current", out);
  rightOut << newNumber << ' ' << newName << '\n'
           << newNumber << ' ' << newName << '\n';
  BOOST_CHECK_EQUAL(out.str(), rightOut.str());
}

BOOST_FIXTURE_TEST_CASE(test_insert_nonexistent_mark, Fixture)
{
  interface.insert(PhonebookInterface::BEFORE, "nonexistent mark", newRecord, out);
  interface.insert(PhonebookInterface::AFTER, "nonexistent mark", newRecord, out);
  rightOut << INVALID_BOOKMARK << INVALID_BOOKMARK;
  BOOST_CHECK_EQUAL(out.str(), rightOut.str());
}

BOOST_FIXTURE_TEST_CASE(test_insert_empty, Fixture)
{
  interfaceEmpty.insert(PhonebookInterface::AFTER, "current", newRecord, out);
  interfaceEmpty.show("current", out);
  rightOut << newNumber << ' ' << newName << '\n';
  BOOST_CHECK_EQUAL(out.str(), rightOut.str());
}

BOOST_FIXTURE_TEST_CASE(test_delete, Fixture)
{
  interface.move("current", stepsLast, out);
  interface.deleteRecord("current", out);
  interface.show("current", out);
  interface.move("current", stepsFirst, out);
  interface.deleteRecord("current", out);
  interface.show("current", out);
  rightOut << number2 << ' ' << name2 << '\n'
           << number2 << ' ' << name2 << '\n';
  BOOST_CHECK_EQUAL(out.str(), rightOut.str());
}

BOOST_FIXTURE_TEST_CASE(test_delete_empty, Fixture)
{
  interfaceEmpty.deleteRecord("current", out);
  rightOut << EMPTY;
  BOOST_CHECK_EQUAL(out.str(), rightOut.str());
}

BOOST_FIXTURE_TEST_CASE(test_delete_nonexistent_mark, Fixture)
{
  interface.deleteRecord("nonexistent mark", out);
  rightOut << INVALID_BOOKMARK;
  BOOST_CHECK_EQUAL(out.str(), rightOut.str());
}

BOOST_FIXTURE_TEST_CASE(test_show, Fixture)
{
  interface.show("current", out);
  interface.move("current", stepForward, out);
  interface.show("current", out);
  interface.move("current", stepForward, out);
  interface.show("current", out);
  rightOut << number1 << ' ' << name1 << '\n'
           << number2 << ' ' << name2 << '\n'
           << number3 << ' ' << name3 << '\n';
  BOOST_CHECK_EQUAL(out.str(), rightOut.str());
}

BOOST_FIXTURE_TEST_CASE(test_show_empty, Fixture)
{
  interfaceEmpty.show("current", out);
  rightOut << EMPTY;
  BOOST_CHECK_EQUAL(out.str(), rightOut.str());
}

BOOST_FIXTURE_TEST_CASE(test_nonexistent_mark, Fixture)
{
  interface.show("nonexistent mark", out);
  rightOut << INVALID_BOOKMARK;
  BOOST_CHECK_EQUAL(out.str(), rightOut.str());
}

BOOST_FIXTURE_TEST_CASE(test_move_to_position, Fixture)
{
  interface.move("current", stepsFirst, out);
  interface.show("current", out);
  interface.move("current", stepsLast, out);
  interface.show("current", out);
  rightOut << number1 << ' ' << name1 << '\n'
           << number3 << ' ' << name3 << '\n';
  BOOST_CHECK_EQUAL(out.str(), rightOut.str());
}

BOOST_FIXTURE_TEST_CASE(test_move_to_step, Fixture)
{
  interface.show("current", out);
  interface.move("current", stepForward, out);
  interface.show("current", out);
  interface.move("current", stepForward, out);
  interface.show("current", out);
  interface.move("current", stepBackward, out);
  interface.show("current", out);
  interface.move("current", stepBackward, out);
  interface.show("current", out);
  rightOut << number1 << ' ' << name1 << '\n'
           << number2 << ' ' << name2 << '\n'
           << number3 << ' ' << name3 << '\n'
           << number2 << ' ' << name2 << '\n'
           << number1 << ' ' << name1 << '\n';
  BOOST_CHECK_EQUAL(out.str(), rightOut.str());
}

BOOST_FIXTURE_TEST_CASE(test_move_invalid, Fixture)
{
  interface.move("current", stepsInvalid, out);
  rightOut << INVALID_STEP;
  BOOST_CHECK_EQUAL(out.str(), rightOut.str());
}

BOOST_FIXTURE_TEST_CASE(test_move_nonexistent_mark, Fixture)
{
  interface.move("nonexistent mark", stepForward, out);
  rightOut << INVALID_BOOKMARK;
  BOOST_CHECK_EQUAL(out.str(), rightOut.str());
}

BOOST_AUTO_TEST_SUITE_END()
