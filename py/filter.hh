#ifndef _FILTER_HH
# define _FILTER_HH

# include <iostream>
# include <iterator>
# include "range.hh"

namespace py
{
  template <typename I, typename F>
  struct filter_iterator
  {
    I current_;
    I end_;
    F pred_;

    typedef std::input_iterator_tag iterator_category;
    typedef typename std::remove_reference<decltype(*I())>::type
                                    value_type;
    typedef std::ptrdiff_t          difference_type;
    typedef value_type*             pointer;
    typedef value_type&             reference;

    filter_iterator(I current, I end, F f)
      : current_(current), end_(end), pred_(f)
    {
      while ((current_ != end_) && (not pred_(*current_))) {
        ++current_;
      }
    }

    value_type operator*() { return *current_; }
    filter_iterator& operator++()
    {
      do {
        ++current_;
      } while ((current_ != end_) && (not pred_(*current_)));
      return *this;
    }
    filter_iterator operator++(int)
    {
      auto orig = *this; ++(*this); return orig; }
    bool operator!=(const filter_iterator& rhs)
    { return current_ != rhs.current_; }
    bool operator==(const filter_iterator& rhs)
    { return current_ == rhs.current_; }
  };

  template <typename F, typename T>
  auto ifilter(F f, T& c)
  {
    typedef filter_iterator<typename T::iterator, F> iterator;
    return py::range<iterator>(iterator(c.begin(), c.end(), f),
                               iterator(c.end(), c.end(), f));
  }

  template <typename F, typename T>
  auto filter(F f, T& c)
  {
    return list(ifilter(f, c));
  }
}

#endif /* _FILTER_HH */

