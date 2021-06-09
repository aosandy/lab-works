#include "tasks.hpp"

#include <iostream>
#include <string>

#include "phonebook.hpp"
#include "phonebook_interface.hpp"
#include "parsers.hpp"
#include "factorial_container.hpp"

void doTask1()
{
  PhonebookInterface phonebook;
  std::string strCommand;
  while (std::getline(std::cin, strCommand))
  {
    Command command = parse(strCommand);
    command(phonebook, std::cout);
  }
}

void doTask2()
{
  FactorialContainer factorials(10);
  for (auto i : factorials)
  {
    std::cout << i << " ";
  }
  std::cout << '\n';
  std::copy(factorials.rbegin(), factorials.rend(), std::ostream_iterator<size_t>(std::cout, " "));
  std::cout << '\n';
}
