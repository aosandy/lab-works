#include <iostream>
#include <stdexcept>
#include <sstream>
#include <cstdlib>
#include <ctime>

#include "tasks.hpp"

int main(int argc, char* argv[])
{
  try
  {
    if ((argc < 2) || (argc > 4))
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
      {
        if (argc != 3)
        {
          std::cerr << "Wrong arguments number\n";
          return 1;
        }
        try
        {
          doTask1(argv[2]);
        }
        catch (const std::exception& e)
        {
          std::cerr << e.what() << '\n';
          return 2;
        }
        break;
      }

      case 2:
      {
        if (argc != 3)
        {
          std::cerr << "Wrong arguments number\n";
          return 1;
        }
        try
        {
          doTask2(argv[2]);
        }
        catch (const std::exception& e)
        {
          std::cerr << e.what() << '\n';
          return 2;
        }
        break;
      }

      case 3:
      {
        if (argc != 2)
        {
          std::cerr << "Wrong arguments number\n";
          return 1;
        }
        try
        {
          doTask3();
        }
        catch (const std::exception& e)
        {
          std::cerr << e.what() << '\n';
          return 2;
        }
        break;
      }

      case 4:
      {
        if (argc != 4)
        {
          std::cerr << "Wrong arguments number\n";
          return 1;
        }
        std::stringstream sizeStream(argv[3]);
        int size = 0;
        sizeStream >> size;
        if (!sizeStream.eof())
        {
          std::cerr << "Wrong size of array\n";
          return 1;
        }
        std::srand(static_cast<double>(std::time(nullptr)));
        try
        {
          doTask4(argv[2], size);
        }
        catch (const std::exception& e)
        {
          std::cerr << e.what() << '\n';
          return 2;
        }
        break;
      }

      default:
      {
        std::cerr << "Wrong task number\n";
        return 1;
      }
    }
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 2;
  }

  return 0;
}
