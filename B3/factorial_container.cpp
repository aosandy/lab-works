#include "factorial_container.hpp"

#include <stdexcept>

const_iterator::pointer const_iterator::operator->() const
{
  return factorial_;
}

const_iterator::reference const_iterator::operator*() const
{
  return factorial_;
}

const_iterator &const_iterator::operator++()
{
  if (number_ > maxNumber_)
  {
    throw std::out_of_range("Iterator moved out of container range");
  }
  factorial_ *= ++number_;
  return *this;
}

const_iterator const_iterator::operator++(int)
{
  const_iterator iterator = *this;
  ++(*this);
  return iterator;
}

const_iterator &const_iterator::operator--()
{
  if (number_ <= 1)
  {
    throw std::out_of_range("Iterator moved out of container range");
  }
  factorial_ /= number_--;
  return *this;
}

const_iterator const_iterator::operator--(int)
{
  const_iterator iterator = *this;
  --(*this);
  return iterator;
}

bool const_iterator::operator==(const const_iterator &iterator) const
{
  return number_ == iterator.number_;
}

bool const_iterator::operator!=(const const_iterator &iterator) const
{
  return number_ != iterator.number_;
}

const_iterator::const_iterator(size_t number, size_t factorial, size_t maxNumber):
  number_(number),
  factorial_(factorial),
  maxNumber_(maxNumber)
{}

FactorialContainer::FactorialContainer(size_t maxNumber):
  maxNumber_(maxNumber),
  maxFactorial_(1)
{
  for (size_t i = 1; i <= maxNumber_ + 1; i++)
  {
    if (maxFactorial_ > SIZE_MAX / i)
    {
      throw std::overflow_error("Factorial value is too big");
    }
    maxFactorial_ *= i;
  }
}

const_iterator FactorialContainer::begin() const
{
  return const_iterator(1, 1, maxNumber_);
}

const_iterator FactorialContainer::end() const
{
  return const_iterator(maxNumber_ + 1, maxFactorial_, maxNumber_);
}

FactorialContainer::const_reverse_iterator FactorialContainer::rbegin() const
{
  return std::make_reverse_iterator(end());
}

FactorialContainer::const_reverse_iterator FactorialContainer::rend() const
{
  return std::make_reverse_iterator(begin());
}
