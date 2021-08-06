#include "phonebook_interface.hpp"

#include <ostream>
#include <stdexcept>
#include <string>

PhonebookInterface::PhonebookInterface():
  bookmarks_({{"current", phonebook_.begin()}})
{}

void PhonebookInterface::add(const Phonebook::record_t &rec, std::ostream &)
{
  if (phonebook_.isEmpty())
  {
    phonebook_.pushBack(rec);
    moveMarks();
  }
  else
  {
    phonebook_.pushBack(rec);
  }
}

void PhonebookInterface::store(const std::string &name, const std::string &newName, std::ostream &out)
{
  auto mark = bookmarks_.find(name);
  if (mark != bookmarks_.end())
  {
    bookmarks_.emplace(newName, mark->second);
  }
  else
  {
    displayErrorMessage(INVALID_BOOKMARK, out);
  }
}

void PhonebookInterface::insert(PhonebookInterface::Place place, const std::string &name,
    const Phonebook::record_t &rec, std::ostream &out)
{
  auto mark = bookmarks_.find(name);
  if (mark == bookmarks_.end())
  {
    displayErrorMessage(INVALID_BOOKMARK, out);
    return;
  }
  if (phonebook_.isEmpty())
  {
    phonebook_.pushBack(rec);
    moveMarks();
  }
  else
  {
    if (place == BEFORE)
    {
      phonebook_.insertBefore(mark->second, rec);
    }
    else if (place == AFTER)
    {
      if (mark->second == std::prev(phonebook_.end()))
      {
        phonebook_.pushBack(rec);
      } else
      {
        phonebook_.insertAfter(mark->second, rec);
      }
    }
  }
}

void PhonebookInterface::deleteRecord(const std::string& name, std::ostream &out)
{
  auto mark = bookmarks_.find(name);
  if (mark == bookmarks_.end())
  {
    displayErrorMessage(INVALID_BOOKMARK, out);
    return;
  }
  if (phonebook_.isEmpty())
  {
    displayErrorMessage(EMPTY, out);
    return;
  }
  auto markRec = mark->second;
  std::string markName = mark->first;
  for (auto &bookmark : bookmarks_)
  {
    if (bookmark.second == markRec)
    {
      bookmark.second++;
    }
  }
  phonebook_.erase(markRec);
  if (!phonebook_.isEmpty())
  {
    moveMarks();
  }
}

void PhonebookInterface::show(const std::string& name, std::ostream &out) const
{
  const auto mark = bookmarks_.find(name);
  if (mark == bookmarks_.end())
  {
    displayErrorMessage(INVALID_BOOKMARK, out);
    return;
  }
  if (phonebook_.isEmpty())
  {
    displayErrorMessage(EMPTY, out);
    return;
  }
  out << mark->second->number << " " << mark->second->name << '\n';
}

void PhonebookInterface::move(const std::string &name, steps_t steps, std::ostream &out)
{
  if (steps.storedType == INVALID)
  {
    displayErrorMessage(INVALID_STEP, out);
    return;
  }
  auto mark = bookmarks_.find(name);
  if (mark == bookmarks_.end())
  {
    displayErrorMessage(INVALID_BOOKMARK, out);
    return;
  }
  if (steps.storedType == KEYWORD)
  {
    if (steps.keyword == FIRST)
    {
      mark->second = phonebook_.begin();
    }
    else if (steps.keyword == LAST)
    {
      mark->second = std::prev(phonebook_.end());
    }
  }
  if (steps.storedType == NUMERIC)
  {
    int stepsNum = steps.steps;
    if (stepsNum > 0)
    {
      if (std::distance(mark->second, --phonebook_.end()) < stepsNum)
      {
        mark->second = --phonebook_.end();
      }
      else
      {
        mark->second = std::next(mark->second, stepsNum);
      }
    }
    else
    {
      if (std::distance(mark->second, phonebook_.begin()) < -stepsNum)
      {
        mark->second = phonebook_.begin();
      }
      else
      {
        mark->second = std::next(mark->second, stepsNum);
      }
    }

  }
}

void PhonebookInterface::moveMarks()
{
  for (auto & bookmark : bookmarks_)
  {
    if (bookmark.second == phonebook_.end())
    {
      bookmark.second = std::prev(phonebook_.end());
    }
  }
}

void PhonebookInterface::displayErrorMessage(PhonebookInterface::ErrorMessage message, std::ostream &out)
{
  switch (message)
  {
    case PhonebookInterface::ErrorMessage::EMPTY:
      out << "<EMPTY>\n";
      break;
    case PhonebookInterface::ErrorMessage::INVALID_STEP:
      out << "<INVALID STEP>\n";
      break;
    case PhonebookInterface::ErrorMessage::INVALID_COMMAND:
      out << "<INVALID COMMAND>\n";
      break;
    case PhonebookInterface::ErrorMessage::INVALID_BOOKMARK:
      out << "<INVALID BOOKMARK>\n";
      break;
    default:
      break;
  }
}
