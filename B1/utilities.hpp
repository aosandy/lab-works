#ifndef B1_UTILITIES_HPP
#define B1_UTILITIES_HPP

#include <iostream>
#include <cstring>
#include <stdexcept>
#include <functional>

template <typename Container>
void print(const Container& container, std::ostream& out, const char* delimiter)
{
  if (!delimiter)
  {
    throw std::invalid_argument("Empty delimiter");
  }
  for (typename Container::const_iterator i = container.begin(); i != container.end(); i++)
  {
    out << *i;
    if (i != container.end())
    {
      out << delimiter;
    }
  }
}

template <typename T>
std::function<bool(const T&, const T&)> getComparator(const char *order)
{
  if (!order)
  {
    throw std::invalid_argument("Order is empty");
  }
  if (std::strcmp(order, "ascending") == 0)
  {
    return std::greater<T>();
  }
  if (std::strcmp(order, "descending") == 0)
  {
    return std::less<T>();
  }
  throw std::invalid_argument("This is not order");
}

template <template <typename> class Policy, typename Container>
void doBubbleSort(Container& container, std::function<bool(const typename Container::value_type&,
    const typename Container::value_type&)> compare)
{
  if (container.empty())
  {
    return;
  }
  using value_type = typename Policy<Container>::value_type;
  using index_t = typename Policy<Container>::index_t;
  const index_t indexBegin = Policy<Container>::begin(container);
  const index_t indexEnd = Policy<Container>::end(container);
  for (index_t i = indexBegin; i != indexEnd; i++)
  {
    for (index_t j = i; j != indexEnd; j++)
    {
      value_type& itemCurr = Policy<Container>::get(container, i);
      value_type& itemNext = Policy<Container>::get(container, j);
      if (compare(itemCurr, itemNext))
      {
        std::swap(itemCurr, itemNext);
      }
    }
  }
}

#endif
