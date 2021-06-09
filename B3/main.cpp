#include <iostream>
#include <sstream>
#include <stdexcept>

#include "tasks.hpp"

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    std::cerr << "Wrong arguments number\n";
    return 1;
  }
  int number = 0;
  std::istringstream numberStream(argv[1]);
  numberStream >> number;
  if (!numberStream.eof())
  {
    std::cerr << "Wrong number of task\n";
    return 1;
  }
  switch (number)
  {
    case 1:
      doTask1();
      break;
    case 2:
      try
      {
        doTask2();
      }
      catch (std::exception &ex)
      {
        std::cerr << ex.what() << '\n';
        return 2;
      }
      break;
    default:
      std::cerr << "Wrong number of task\n";
      return 1;
  }
  return 0;
}
