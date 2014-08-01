#ifndef _LIST_HH
# define _LIST_HH

# include <vector>
# include <initializer_list>

namespace py
{
  template <typename T>
  auto list(const T& r)
    -> std::vector<typename T::value_type>
  {
    return std::vector<typename T::value_type>(r.begin(), r.end());
  }

  template <typename T>
  auto list(const std::initializer_list<T>& r)
    -> std::vector<T>
  {
    return std::vector<T>(r.begin(), r.end());
  }
}

#endif /* _LIST_HH */

