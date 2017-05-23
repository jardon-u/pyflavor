#ifndef _MAP_HH
# define _MAP_HH

# include <type_traits>
# include <utility>
# include "internal.hh"
# include "transformed_iterator.hh"
# include "list.hh"

namespace py
{
  template <typename T, typename F>
  auto imap(const F& f, T& c)
  {
    using namespace internal;
    static_assert(has_member_begin<T>::value, "c.begin must be defined");
    static_assert(has_member_end<T>::value, "c.end must be defined");
    static_assert(is_callable<F>::value, "f must be callable");

    typedef transformed_iterator<typename T::iterator, F> iterator;
    return py::range<iterator>(iterator(c.begin(), f),
                               iterator(c.end(), f));
  }

  template <typename T, typename F>
  auto operator|(T& c, const F& f)
  {
    return imap(f, c);
  }

  template <typename T, typename F>
  auto map(const F& f, T& c)
  {
    return list(imap(f, c));
  }
}

#endif /* _MAP_HH */
