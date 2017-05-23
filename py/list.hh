#ifndef _LIST_HH
# define _LIST_HH

# include <vector>
# include <initializer_list>

namespace py
{
  // template<typename T>
  // struct list : public std::vector<T>
  // {
  //   template <typename U>
  //   bool operator==(const U& v);
  // };

  template <typename T>
  auto list(const T& container)
    -> std::vector<typename T::value_type>
  {
    return std::vector<typename T::value_type>(container.begin(), container.end());
  }

  template <typename T>
  auto list(const std::initializer_list<T>& container)
    -> std::vector<T>
  {
    return std::vector<T>(container.begin(), container.end());
  }
}

#endif /* _LIST_HH */
