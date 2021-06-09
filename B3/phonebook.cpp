#include "phonebook.hpp"

void Phonebook::replace(const iterator &it, const record_t &rec)
{
  *it = rec;
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
