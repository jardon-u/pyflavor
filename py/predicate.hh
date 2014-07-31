#ifndef _PREDICATE_HH
# define _PREDICATE_HH

# include <algorithm>

namespace py
{
  template <typename T>
  bool all(const T& c)
  {
    return std::all_of(c.begin(), c.end(), [](bool b) { return b; } );
  }

  template <typename T>
  bool any(const T& c)
  {
    return std::any_of(c.begin(), c.end(), [](bool b) { return b; });
  }

  template <typename T>
  bool none(const T& c)
  {
    return std::none_of(c.begin(), c.end(), [](bool b) { return b; });
  }
}

#endif /* _PREDICATE_HH */

