#ifndef _MAP_HH
# define _MAP_HH

# include "transformed.hh"
# include "list.hh"

namespace py
{
  template <typename T, typename F>
  auto imap(F f, T& c)
  {
    //FIXME: check T has begin/end and F is_callable
    typedef transformed_iterator<typename T::iterator, F> iterator;
    return py::range<iterator>(iterator(c.begin(), f),
                               iterator(c.end(), f));
  }

  template <typename T, typename F>
  auto operator|(T& c, F f)
  {
    return imap(f, c);
  }

  template <typename T, typename F>
  auto map(F f, T& c)
  {
    return list(imap(f, c));
  }
}

#endif /* _MAP_HH */

