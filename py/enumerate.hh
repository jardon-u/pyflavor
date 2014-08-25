#ifndef _ENUMERATE_HH
# define _ENUMERATE_HH

# include <tuple>
# include "range.hh"

namespace py
{
  namespace {
    template <typename I>
    struct enumerate_iterator
    {
      int i = 0;
      I iter;

      typedef std::input_iterator_tag            iterator_category;
      typedef decltype(std::make_tuple(i,*iter)) value_type;
      typedef std::ptrdiff_t                     difference_type;
      typedef value_type*                        pointer;
      typedef value_type&                        reference;

      enumerate_iterator(I iter)
        : iter(iter)
      {}

      //FIXME: maybe not a temporary here
      value_type operator*() { return std::make_tuple(i,*iter); }
      enumerate_iterator& operator++() { ++iter; ++i; return *this; }
      enumerate_iterator operator++(int)
      { auto orig = *this; ++(*this); return orig; }
      bool operator!=(const enumerate_iterator& x)
      { return iter != x.iter && i != x.i; }
      bool operator==(const enumerate_iterator& x)
      { return iter == x.iter && i == x.i; }
    };
  }

  template <typename T>
  auto enumerate(const T& r)
  {
    typedef enumerate_iterator<typename T::iterator> iterator;
    return py::range<iterator>(iterator(r.begin()), iterator(r.end()));
  }

}

#endif /* _ENUMERATE_HH */

