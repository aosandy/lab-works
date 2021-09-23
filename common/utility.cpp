#include "utility.hpp"

#include <istream>
#include <cctype>

std::istream& skipWS(std::istream &stream)
{
  while (std::isblank(stream.peek()))
  {
    stream.get();
  }
  return stream;
}
