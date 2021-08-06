#include <sstream>
#include <string>

#include <boost/test/unit_test.hpp>

#include "parsers.hpp"

BOOST_AUTO_TEST_SUITE(parsers)

struct Fixture
{
  std::stringstream stream;
  std::string input;
  Command command;
  PhonebookInterface phonebook;
  const std::string INVALID_COMMAND = "<INVALID COMMAND>\n";
  const PhonebookInterface::steps_t stepsLast = {PhonebookInterface::LAST,
      PhonebookInterface::KEYWORD};
};

BOOST_FIXTURE_TEST_CASE(test_record_input, Fixture)
{
  input = "123 \"abc\"";
  std::string rightNumber = "123";
  std::string rightName = "abc";
  Phonebook::record_t record;
  stream << input;
  stream >> record;
  BOOST_CHECK_EQUAL(record.number, rightNumber);
  BOOST_CHECK_EQUAL(record.name, rightName);
  BOOST_CHECK(!stream.fail());
}

BOOST_FIXTURE_TEST_CASE(test_invalid_record_input, Fixture)
{
  Phonebook::record_t record;
  input = "12 3 \"abc\"";
  stream << input;
  stream >> record;
  BOOST_CHECK(stream.fail());
  stream.str("");
  stream.clear();
  input = "1r23 \"abc\"";
  stream << input;
  stream >> record;
  BOOST_CHECK(stream.fail());
  stream.str("");
  stream.clear();
  input = "123 abc";
  stream << input;
  stream >> record;
  BOOST_CHECK(stream.fail());
  stream.str("");
  stream.clear();
  input = "123abc";
  stream << input;
  stream >> record;
  BOOST_CHECK(stream.fail());
}

BOOST_FIXTURE_TEST_CASE(test_place_input, Fixture)
{
  PhonebookInterface::Place place;
  input = "before";
  stream << input;
  stream >> place;
  BOOST_CHECK_EQUAL(place, PhonebookInterface::BEFORE);
  BOOST_CHECK(!stream.fail());
  stream.str("");
  stream.clear();
  input = "after";
  stream << input;
  stream >> place;
  BOOST_CHECK_EQUAL(place, PhonebookInterface::AFTER);
  BOOST_CHECK(!stream.fail());
}

BOOST_FIXTURE_TEST_CASE(test_invalid_place_input, Fixture)
{
  PhonebookInterface::Place place;
  input = "invalid";
  stream << input;
  stream >> place;
  BOOST_CHECK(stream.fail());
}

BOOST_FIXTURE_TEST_CASE(test_step_input, Fixture)
{
  PhonebookInterface::steps_t steps;
  input = "first";
  stream << input;
  stream >> steps;
  BOOST_CHECK_EQUAL(steps.keyword, PhonebookInterface::FIRST);
  BOOST_CHECK_EQUAL(steps.storedType, PhonebookInterface::KEYWORD);
  BOOST_CHECK(!stream.fail());
  stream.str("");
  stream.clear();
  input = "last";
  stream << input;
  stream >> steps;
  BOOST_CHECK_EQUAL(steps.keyword, PhonebookInterface::LAST);
  BOOST_CHECK_EQUAL(steps.storedType, PhonebookInterface::KEYWORD);
  BOOST_CHECK(!stream.fail());
  stream.str("");
  stream.clear();
  input = "5";
  stream << input;
  stream >> steps;
  BOOST_CHECK_EQUAL(steps.steps, 5);
  BOOST_CHECK_EQUAL(steps.storedType, PhonebookInterface::NUMERIC);
  BOOST_CHECK(!stream.fail());
}

BOOST_FIXTURE_TEST_CASE(test_invalid_step_input, Fixture)
{
  PhonebookInterface::steps_t steps;
  input = "invalid";
  stream << input;
  stream >> steps;
  BOOST_CHECK_EQUAL(steps.storedType, PhonebookInterface::INVALID);
  BOOST_CHECK(stream.fail());
}

BOOST_FIXTURE_TEST_CASE(test_invalid_add_parser, Fixture)
{
  input = "add 123a \"abc\"";
  command = parse(input);
  command(phonebook, stream);
  BOOST_CHECK_EQUAL(stream.str(), INVALID_COMMAND);
}

BOOST_FIXTURE_TEST_CASE(test_invalid_store_parser, Fixture)
{
  input = "store current mark1 mark1";
  command = parse(input);
  command(phonebook, stream);
  BOOST_CHECK_EQUAL(stream.str(), INVALID_COMMAND);
}

BOOST_FIXTURE_TEST_CASE(test_invalid_insert_parser, Fixture)
{
  input = "insert insert after current 123 \"abc\"";
  command = parse(input);
  command(phonebook, stream);
  BOOST_CHECK_EQUAL(stream.str(), INVALID_COMMAND);
}

BOOST_FIXTURE_TEST_CASE(test_invalid_delete_parser, Fixture)
{
  phonebook.add({"123", "abc"}, stream);
  input = "delete current no";
  command = parse(input);
  command(phonebook, stream);
  BOOST_CHECK_EQUAL(stream.str(), INVALID_COMMAND);
}

BOOST_FIXTURE_TEST_CASE(test_invalid_show_parser, Fixture)
{
  phonebook.add({"123", "abc"}, stream);
  input = "show 0 current";
  command = parse(input);
  command(phonebook, stream);
  BOOST_CHECK_EQUAL(stream.str(), INVALID_COMMAND);
}

BOOST_FIXTURE_TEST_CASE(test_invalid_move_parser, Fixture)
{
  phonebook.add({"123", "abc"}, stream);
  input = "move current fist";
  command = parse(input);
  command(phonebook, stream);
  BOOST_CHECK_EQUAL(stream.str(), "<INVALID STEP>\n");
}

BOOST_FIXTURE_TEST_CASE(test_slash_processing, Fixture)
{
  input = R"(add 123 "\\\\b")";
  command = parse(input);
  command(phonebook, stream);
  phonebook.show("current", stream);
  BOOST_CHECK_EQUAL(stream.str(), "123 \\\\b\n");
  stream.str("");
  input = R"(add 456 "\\a\\\\b\\\\\"\"c\\\\")";
  command = parse(input);
  command(phonebook, stream);
  phonebook.move("current", stepsLast, stream);
  phonebook.show("current", stream);
  BOOST_CHECK_EQUAL(stream.str(), "456 \\a\\\\b\\\\\"\"c\\\\\n");
}

BOOST_AUTO_TEST_SUITE_END()
