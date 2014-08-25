#ifndef _PREDICATE_HH
# define _PREDICATE_HH

# include <algorithm>
# include <type_traits>

namespace py
{
  template <typename T>
  bool all(const T& c)
  {
    static_assert(std::is_same<bool, typename T::value_type>::value,
                  "c should have bool value type");
    return std::all_of(c.begin(), c.end(), [](bool b) { return b; } );
  }

  template <typename T>
  bool any(const T& c)
  {
    static_assert(std::is_same<bool, typename T::value_type>::value,
                  "c should have bool value type");
    return std::any_of(c.begin(), c.end(), [](bool b) { return b; });
  }

  template <typename T>
  bool none(const T& c)
  {
    static_assert(std::is_same<bool, typename T::value_type>::value,
                  "c should have bool value type");
    return std::none_of(c.begin(), c.end(), [](bool b) { return b; });
  }
}

#endif /* _PREDICATE_HH */

