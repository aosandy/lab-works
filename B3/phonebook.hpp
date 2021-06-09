#ifndef B3_PHONEBOOK_HPP
#define B3_PHONEBOOK_HPP

#include <list>
#include <string>

class Phonebook
{
public:
  struct record_t
  {
    std::string name;
    std::string number;
  };
  using iterator = std::list<record_t>::iterator;
  using const_iterator = std::list<record_t>::const_iterator;

  void replace(const iterator&, const record_t&);
  iterator erase(const iterator&);
  iterator insertBefore(const iterator&, const record_t&);
  iterator insertAfter(const iterator&, const record_t&);
  void pushBack(const record_t&);
  iterator begin();
  iterator end();
  const_iterator cbegin() const;
  const_iterator cend() const;
  bool isEmpty() const;

private:
  std::list<record_t> records_;
};

#endif
