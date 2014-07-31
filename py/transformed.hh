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
    typedef decltype(f(*iter)) value_type;
    typedef std::ptrdiff_t difference_type;
    typedef value_type* pointer;
    typedef value_type& reference;

    transformed_iterator(I iter, F f)
      : iter(iter), f(f)
    {
    }

    decltype(f(*iter)) operator*()  { return f(*iter); }
    transformed_iterator& operator++() { ++iter; return *this; }
    transformed_iterator operator++(int) { auto orig = *this; ++(*this); return orig; }
    bool operator!=(const transformed_iterator& x) { return iter != x.iter; }
    bool operator==(const transformed_iterator& x) { return iter == x.iter; }
  };

  template <typename T, typename F>
  auto transformed(T& range, F f)
  {
    //FIXME: check T has begin/end and F is_callable
    typedef transformed_iterator<typename T::iterator, F> iterator;
    return py::range<iterator>(iterator(range.begin(), f),
                               iterator(range.end(), f));
  }

  template <typename T, typename F>
  auto operator|(T& range, F f)
  {
    //FIXME: check T has begin/end and F is_callable
    typedef transformed_iterator<typename T::iterator, F> iterator;
    return py::range<iterator>(iterator(range.begin(), f),
                               iterator(range.end(), f));
  }
}

#endif /* _TRANSFORMED_HH */

