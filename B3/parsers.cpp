#include "parsers.hpp"

#include <iostream>
#include <string>
#include <functional>

bool validMark(const std::string &markName);

Command parse(const std::string &parseLine)
{
  std::istringstream in(parseLine);
  std::string command;
  in >> command;
  auto commandIt = details::Commands.find(command);
  if (commandIt == details::Commands.end())
  {
    return std::bind(&PhonebookInterface::displayErrorMessage,
        PhonebookInterface::ErrorMessage::INVALID_COMMAND, std::placeholders::_2);
  }
  return commandIt->second(in);
}

std::istream& operator>>(std::istream &in, PhonebookInterface::Place &place)
{
  std::string strPlace;
  in >> std::ws;
  if (!in)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  in >> strPlace;
  if (strPlace == "before")
  {
    place = PhonebookInterface::BEFORE;
  }
  else if (strPlace == "after")
  {
    place = PhonebookInterface::AFTER;
  }
  else
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream& operator>>(std::istream &in, PhonebookInterface::steps_t &steps)
{
  std::string strSteps;
  in >> std::ws;
  if (!in)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  in >> strSteps;
  if (strSteps == "first")
  {
    steps.storedType = PhonebookInterface::KEYWORD;
    steps.keyword = PhonebookInterface::FIRST;
  }
  else if (strSteps == "last")
  {
    steps.storedType = PhonebookInterface::KEYWORD;
    steps.keyword = PhonebookInterface::LAST;
  }
  else
  {
    int intSteps;
    std::istringstream stream(strSteps);
    stream >> intSteps;
    if (stream.eof())
    {
      steps.storedType = PhonebookInterface::NUMERIC;
      steps.steps = intSteps;
    }
    else
    {
      steps.storedType = PhonebookInterface::INVALID;
      in.setstate(std::ios::failbit);
    }
  }
  return in;
}

Command details::parseAdd(std::istringstream &in)
{
  Phonebook::record_t rec;
  in >> rec >> std::ws;
  if (!in || !in.eof())
  {
    return std::bind(PhonebookInterface::displayErrorMessage,
        PhonebookInterface::ErrorMessage::INVALID_COMMAND, std::placeholders::_2);
  }
  return std::bind(&PhonebookInterface::add, std::placeholders::_1, rec, std::placeholders::_2);
}

Command details::parseStore(std::istringstream &in)
{
  std::string name;
  std::string newName;
  in >> name >> newName >> std::ws;
  if (!validMark(name) || !validMark(newName) || !in || !in.eof())
  {
    return std::bind(&PhonebookInterface::displayErrorMessage,
        PhonebookInterface::ErrorMessage::INVALID_COMMAND, std::placeholders::_2);
  }
  return std::bind(&PhonebookInterface::store, std::placeholders::_1, name, newName, std::placeholders::_2);
}

Command details::parseInsert(std::istringstream &in)
{
  PhonebookInterface::Place place;
  std::string name;
  Phonebook::record_t rec;
  in >> place >> name >> rec >> std::ws;
  if (!validMark(name) || !in || !in.eof())
  {
    return std::bind(&PhonebookInterface::displayErrorMessage,
        PhonebookInterface::ErrorMessage::INVALID_COMMAND, std::placeholders::_2);
  }
  return std::bind(&PhonebookInterface::insert, std::placeholders::_1, place, name, rec, std::placeholders::_2);
}

Command details::parseDelete(std::istringstream &in)
{
  std::string name;
  in >> name >> std::ws;
  if (!validMark(name) || !in || !in.eof())
  {
    return std::bind(&PhonebookInterface::displayErrorMessage,
        PhonebookInterface::ErrorMessage::INVALID_COMMAND, std::placeholders::_2);
  }
  return std::bind(&PhonebookInterface::deleteRecord, std::placeholders::_1, name, std::placeholders::_2);
}

Command details::parseShow(std::istringstream &in)
{
  std::string name;
  in >> name >> std::ws;
  if (!validMark(name) || !in || !in.eof())
  {
    return std::bind(&PhonebookInterface::displayErrorMessage,
        PhonebookInterface::ErrorMessage::INVALID_COMMAND, std::placeholders::_2);
  }
  return std::bind(&PhonebookInterface::show, std::placeholders::_1, name, std::placeholders::_2);
}

Command details::parseMove(std::istringstream &in)
{
  std::string name;
  PhonebookInterface::steps_t steps;
  in >> name;
  if (!validMark(name) || !in)
  {
    return std::bind(&PhonebookInterface::displayErrorMessage,
        PhonebookInterface::ErrorMessage::INVALID_COMMAND, std::placeholders::_2);
  }
  in >> steps >> std::ws;
  if (!in.eof())
  {
    return std::bind(&PhonebookInterface::displayErrorMessage,
        PhonebookInterface::ErrorMessage::INVALID_STEP, std::placeholders::_2);
  }
  return std::bind(&PhonebookInterface::move, std::placeholders::_1, name, steps, std::placeholders::_2);
}

bool validMark(const std::string &markName)
{
  if (markName.empty())
  {
    return false;
  }
  for (char ch : markName)
  {
    if (!std::isalnum(ch) && (ch != '-'))
    {
      return false;
    }
  }
  return true;
}

