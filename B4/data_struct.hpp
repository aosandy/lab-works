#ifndef B4_DATA_STRUCT_HPP
#define B4_DATA_STRUCT_HPP

#include <iosfwd>
#include <string>

struct DataStruct
{
  int key1;
  int key2;
  std::string str;

  friend std::istream &operator>>(std::istream&, DataStruct&);
  friend std::ostream &operator<<(std::ostream&, const DataStruct&);
};

struct DataStructsComparator
{
  bool operator()(const DataStruct&, const DataStruct&) const;
};

#endif
