#include "tasks.hpp"

#include <iostream>
#include <stdexcept>
#include <vector>

#include "utilities.hpp"
#include "policy.hpp"

void fillRandom(double* array, int size);

void doTask4(const char* order, int size)
{
  if (size <= 0)
  {
    throw std::invalid_argument("Size is not positive");
  }
  std::vector<double> vector(size);
  fillRandom(vector.data(), size);
  print(vector, std::cout, " ");
  std::cout << '\n';
  doBubbleSort<IndexPolicy>(vector, getComparator<double>(order));
  print(vector, std::cout, " ");
  std::cout << '\n';
}

void fillRandom(double* array, int size)
{
  if (array == nullptr)
  {
    throw std::invalid_argument("Array is empty");
  }
  for (int i = 0; i < size; i++)
  {
    array[i] = static_cast<double>(rand()) / (RAND_MAX / 2) - 1;
  }
}
