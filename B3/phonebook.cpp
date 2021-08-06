#include "phonebook.hpp"

#include <iostream>
#include <string>

std::istream& operator>>(std::istream &in, Phonebook::record_t &rec)
{
  std::string number;
  in >> std::ws;
  if (!in)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  in >> number;
  if (number.empty())
  {
    return in;
  }
  for (char i : number)
  {
    if (!isdigit(i))
    {
      in.setstate(std::ios::failbit);
      return in;
    }
  }
  std::string name;
  in >> std::ws;
  if (!in)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  char ch = '\0';
  in >> ch;
  if (ch != '\"')
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  bool slashFlag = false;
  while (in.get(ch))
  {
    if (slashFlag)
    {
      slashFlag = false;
      if ((ch == '\\') || (ch == '\"'))
      {
        name.pop_back();
      }
    }
    else
    {
      if (ch == '\"')
      {
        break;
      }
      slashFlag = (ch == '\\');
    }
    name.push_back(ch);
  }
  if (ch != '\"')
  {
    in.setstate(std::ios::failbit);
  }
  rec.name = name;
  rec.number = number;
  return in;
}

Phonebook::iterator Phonebook::erase(const iterator &it)
{
  return records_.erase(it);
}

Phonebook::iterator Phonebook::insertBefore(const iterator &it, const record_t &rec)
{
  return std::next(records_.insert(it, rec));
}

Phonebook::iterator Phonebook::insertAfter(const iterator &it, const record_t &rec)
{
  if (it == records_.end())
  {
    records_.push_back(rec);
    return std::prev(records_.end());
  }
  return std::prev(records_.insert(std::next(it), rec));

}

void Phonebook::pushBack(const record_t &rec)
{
  records_.push_back(rec);
}

Phonebook::iterator Phonebook::begin()
{
  return records_.begin();
}

Phonebook::iterator Phonebook::end()
{
  return records_.end();
}

Phonebook::const_iterator Phonebook::begin() const
{
  return records_.cbegin();
}

Phonebook::const_iterator Phonebook::end() const
{
  return records_.cend();
}

Phonebook::const_iterator Phonebook::cbegin() const
{
  return records_.cbegin();
}

Phonebook::const_iterator Phonebook::cend() const
{
  return records_.cend();
}

bool Phonebook::isEmpty() const
{
  return records_.empty();
}
