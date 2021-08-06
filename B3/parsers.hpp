#ifndef B3_PARSERS_HPP
#define B3_PARSERS_HPP

#include <ostream>
#include <string>
#include <sstream>
#include <functional>

#include "phonebook.hpp"
#include "phonebook_interface.hpp"

using Command = std::function<void(PhonebookInterface&, std::ostream&)>;

Command parse(const std::string&);

std::istream& operator>>(std::istream&, PhonebookInterface::Place&);
std::istream& operator>>(std::istream&, PhonebookInterface::steps_t&);

namespace details
{
  Command parseAdd(std::istringstream&);
  Command parseStore(std::istringstream&);
  Command parseInsert(std::istringstream&);
  Command parseDelete(std::istringstream&);
  Command parseShow(std::istringstream&);
  Command parseMove(std::istringstream&);

  const std::unordered_map<std::string, std::function<Command(std::istringstream&)>> Commands = {
    {"add", parseAdd},
    {"store", parseStore},
    {"insert", parseInsert},
    {"delete", parseDelete},
    {"show", parseShow},
    {"move", parseMove}
  };
}

#endif
