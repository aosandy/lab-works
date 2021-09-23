#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

#include "data_struct.hpp"

int main()
{
  std::vector<DataStruct> dataStructVector((std::istream_iterator<DataStruct>(std::cin)), std::istream_iterator<DataStruct>());
  if (!std::cin && !std::cin.eof())
  {
    std::cerr << "Invalid input";
    return 2;
  }
  std::sort(dataStructVector.begin(), dataStructVector.end(), DataStructsComparator());
  std::copy(dataStructVector.begin(), dataStructVector.end(), std::ostream_iterator<DataStruct>(std::cout, "\n"));
  return 0;
}
