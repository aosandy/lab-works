#include "tasks.hpp"

#include <iostream>
#include <stdexcept>
#include <functional>
#include <vector>
#include <forward_list>

#include "utilities.hpp"
#include "policy.hpp"

void doTask1(const char* order)
{
  std::function<bool(const int&, const int&)> compare = getComparator<int>(order);
  std::vector<int> vectorIndexSort;
  int temp = 0;
  while (std::cin >> temp)
  {
    vectorIndexSort.push_back(temp);
  }
  if (!std::cin.eof())
  {
    throw std::runtime_error("Invalid input data");
  }
  std::vector<int> vectorAtSort(vectorIndexSort);
  std::forward_list<int> listSort(vectorIndexSort.begin(), vectorIndexSort.end());

  doBubbleSort<IndexPolicy>(vectorIndexSort, compare);
  print(vectorIndexSort, std::cout, " ");
  std::cout << '\n';
  doBubbleSort<AtPolicy>(vectorAtSort, compare);
  print(vectorAtSort, std::cout, " ");
  std::cout << '\n';
  doBubbleSort<IteratorPolicy>(listSort, compare);
  print(listSort, std::cout, " ");
  std::cout << '\n';
}
