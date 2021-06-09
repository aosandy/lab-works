#ifndef B3_FACTORIAL_CONTAINER_HPP
#define B3_FACTORIAL_CONTAINER_HPP

#include <iterator>
#include <cstddef>

class const_iterator
{
public:
  using iterator_category = std::bidirectional_iterator_tag;
  using difference_type = std::ptrdiff_t;
  using value_type = size_t;
  using pointer = size_t;
  using reference = size_t;

  pointer operator->() const;
  reference operator*() const;
  const_iterator &operator++();
  const_iterator operator++(int);
  const_iterator &operator--();
  const_iterator operator--(int);
  bool operator==(const const_iterator&) const;
  bool operator!=(const const_iterator&) const;

private:
  friend class FactorialContainer;
  size_t number_;
  size_t factorial_;
  size_t maxNumber_;
  const_iterator(size_t, size_t, size_t);
};

class FactorialContainer
{
public:
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

  explicit FactorialContainer(size_t);

  const_iterator begin() const;
  const_iterator end() const;
  const_reverse_iterator rbegin() const;
  const_reverse_iterator rend() const;

private:
  size_t maxNumber_;
  size_t maxFactorial_;
};

#endif
