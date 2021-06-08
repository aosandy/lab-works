#ifndef B1_POLICY_HPP
#define B1_POLICY_HPP

#include <cstddef>

template <typename Container>
struct IndexPolicy
{
  using value_type = typename Container::value_type;
  using index_t = size_t;

  static index_t begin(Container&)
  {
    return 0;
  }
  static index_t end(Container& container)
  {
    return container.size();
  }
  static value_type& get(Container& container, const index_t& index)
  {
    return container[index];
  }
};

template <typename Container>
struct AtPolicy
{
  using value_type = typename Container::value_type;
  using index_t = size_t;

  static index_t begin(Container&)
  {
    return 0;
  }
  static index_t end(Container& container)
  {
    return container.size();
  }
  static value_type& get(Container& container, const index_t& index)
  {
    return container.at(index);
  }
};

template <typename Container>
struct IteratorPolicy
{
  using value_type = typename Container::value_type;
  using index_t = typename Container::iterator;

  static index_t begin(Container& container)
  {
    return container.begin();
  }
  static index_t end(Container& container)
  {
    return container.end();
  }
  static value_type& get(Container&, const index_t& index)
  {
    return *index;
  }
};

#endif
