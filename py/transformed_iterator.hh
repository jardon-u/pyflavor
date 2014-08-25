#ifndef _TRANSFORMED_HH
# define _TRANSFORMED_HH

# include <iterator>
# include "range.hh"

namespace py
{
  template <typename I, typename F>
  struct transformed_iterator
  {
    I iter;
    F f;

    typedef std::input_iterator_tag iterator_category;
    typedef decltype(f(*iter))      value_type;
    typedef std::ptrdiff_t          difference_type;
    typedef value_type*             pointer;
    typedef value_type&             reference;

    transformed_iterator(I iter, F f)
      : iter(iter), f(f)
    {}

    decltype(f(*iter)) operator*()  { return f(*iter); }
    transformed_iterator& operator++() { ++iter; return *this; }
    transformed_iterator operator++(int)
    { auto orig = *this; ++(*this); return orig; }
    bool operator!=(const transformed_iterator& x)
    { return iter != x.iter; }
    bool operator==(const transformed_iterator& x)
    { return iter == x.iter; }
  };
}

#endif /* _TRANSFORMED_HH */

