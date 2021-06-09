#ifndef B3_PHONEBOOK_INTERFACE_HPP
#define B3_PHONEBOOK_INTERFACE_HPP

#include <unordered_map>
#include <string>
#include "phonebook.hpp"

class PhonebookInterface
{
public:
  enum Place
  {
    BEFORE,
    AFTER
  };

  enum StepsKeywords
  {
    FIRST,
    LAST
  };

  enum StepsValues
  {
    NUMERIC,
    KEYWORD,
    INVALID
  };

  enum ErrorMessage
  {
    EMPTY,
    INVALID_STEP,
    INVALID_COMMAND,
    INVALID_BOOKMARK
  };

  struct steps_t
  {
    union
    {
      StepsKeywords keyword;
      int steps;
    };
    StepsValues storedType;
  };

  PhonebookInterface();

  void add(const Phonebook::record_t&, std::ostream&);
  void store(const std::string&, const std::string&, std::ostream&);
  void insert(Place, const std::string&, const Phonebook::record_t&, std::ostream&);
  void deleteRecord(const std::string&, std::ostream&);
  void show(const std::string&, std::ostream&) const;
  void move(const std::string&, steps_t, std::ostream&);
  void displayErrorMessage(PhonebookInterface::ErrorMessage, std::ostream&) const;

private:
  Phonebook phonebook_;
  std::unordered_map<std::string, Phonebook::iterator> bookmarks_;
  void moveMarks();
};

#endif
