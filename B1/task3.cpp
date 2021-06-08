#include "tasks.hpp"

#include <iostream>
#include <stdexcept>
#include <vector>

#include "utilities.hpp"

void doTask3()
{
  std::vector<int> vector;
  int temp = 1;
  while (std::cin >> temp)
  {
    if (temp == 0)
    {
      break;
    }
    vector.push_back(temp);
  }
  if (std::cin.fail() && !std::cin.eof())
  {
    throw std::runtime_error("Invalid input");
  }
  if (vector.empty())
  {
    return;
  }
  if (temp != 0)
  {
    throw std::runtime_error("End of testVector must be 0");
  }

  std::vector<int>::iterator iterator = vector.begin();
  if (vector.back() == 1)
  {
    while (iterator != vector.end())
    {
      if (*iterator % 2 == 0)
      {
        iterator = vector.erase(iterator);
      }
      else
      {
        iterator++;
      }
    }
  }
  else if (vector.back() == 2)
  {
    while (iterator != vector.end())
    {
      if (*iterator % 3 == 0)
      {
        iterator = vector.insert(iterator + 1, 3, 1) + 3;
      }
      else
      {
        iterator++;
      }
    }
  }
  print(vector, std::cout, " ");
  std::cout << '\n';
}
