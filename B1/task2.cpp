#include "tasks.hpp"

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <memory>
#include <cstring>
#include <vector>

#include "utilities.hpp"

void doTask2(const char* name)
{
  if (name == nullptr)
  {
    throw std::invalid_argument("Name is empty");
  }
  std::ifstream input(name);
  if (!input)
  {
    throw std::runtime_error("File do not open");
  }

  size_t defaultSize = 1024, cnt = 0;
  std::unique_ptr<char[]> array = std::make_unique<char[]>(defaultSize);

  while (input)
  {
    if (defaultSize == cnt)
    {
      defaultSize *= 2;
      std::unique_ptr<char[]> temp = std::make_unique<char[]>(defaultSize);
      std::memcpy(temp.get(), array.get(), cnt);
      array = std::move(temp);
    }
    input.read(array.get() + cnt, defaultSize - cnt);
    cnt += input.gcount();
  }
  if (!input.eof())
  {
    throw std::runtime_error("File is not fully read");
  }

  std::vector<char> vector(array.get(), array.get() + cnt);
  print(vector, std::cout, "");
}
