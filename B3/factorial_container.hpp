#ifndef B3_FACTORIAL_CONTAINER_HPP
#define B3_FACTORIAL_CONTAINER_HPP

#include <iterator>
#include <cstddef>

class FactorialContainer
{
public:
  class const_iterator : public std::iterator<std::bidirectional_iterator_tag,
      size_t, std::ptrdiff_t, size_t, size_t>
  {
  public:
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

  using iterator = const_iterator;
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

  explicit FactorialContainer(size_t maxNumber = 0);

  const_iterator begin() const;
  const_iterator end() const;
  const_reverse_iterator rbegin() const;
  const_reverse_iterator rend() const;

private:
  size_t maxNumber_;
  size_t maxFactorial_;
};

#endif
