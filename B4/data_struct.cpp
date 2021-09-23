#include "data_struct.hpp"

#include <iostream>
#include <string>

#include <boost/io/ios_state.hpp>

#include "utility.hpp"

int readKey(std::istream &input, int minValue, int maxValue)
{
  int key;
  input >> key;
  if (!input || (key < minValue) || (key > maxValue))
  {
    input.setstate(std::ios::failbit);
  }
  return key;
}

std::istream &operator>>(std::istream &input, DataStruct &dataStruct)
{
  std::istream::sentry sentry(input);
  if (!sentry)
  {
    return input;
  }
  boost::io::ios_flags_saver saver(input);
  const char DELIMETER = ',';
  const int MIN_VALUE = -5;
  const int MAX_VALUE = 5;
  input >> std::noskipws >> skipWS;
  int key1 = readKey(input, MIN_VALUE, MAX_VALUE);
  if (!input || (input.get() != DELIMETER))
  {
    input.setstate(std::ios::failbit);
    return input;
  }
  input >> skipWS;
  int key2 = readKey(input, MIN_VALUE, MAX_VALUE);
  if (!input || (input.get() != DELIMETER))
  {
    input.setstate(std::ios::failbit);
    return input;
  }
  input >> skipWS;
  std::string str;
  std::getline(input, str);
  if (!input || str.empty())
  {
    input.setstate(std::ios::failbit);
    return input;
  }

  dataStruct.key1 = key1;
  dataStruct.key2 = key2;
  dataStruct.str = str;
  return input;
}

std::ostream &operator<<(std::ostream &output, const DataStruct &dataStruct)
{
  std::ostream::sentry sentry(output);
  if (!sentry)
  {
    return output;
  }
  const char DELIMETER = ',';
  output << dataStruct.key1 << DELIMETER << dataStruct.key2 << DELIMETER << dataStruct.str;
  return output;
}

bool DataStructsComparator::operator()(const DataStruct &dataStruct1, const DataStruct &dataStruct2) const
{
  if (dataStruct1.key1 != dataStruct2.key1)
  {
    return dataStruct1.key1 < dataStruct2.key1;
  }
  if (dataStruct1.key2 != dataStruct2.key2)
  {
    return dataStruct1.key2 < dataStruct2.key2;
  }
  return dataStruct1.str.length() < dataStruct2.str.length();
}
