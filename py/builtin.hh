#ifndef _BUILTIN_HH
# define _BUILTIN_HH

#include <list>
#include <tuple>
#include <algorithm>
#include <iostream>

namespace py
{
  /// print
  //FIXME: sep and end configurable
  void print() {
    std::cout << std::endl;
  }
  template <typename T, typename ...Args>
  inline
  void print(const T& value, const Args&... args)
  {
    std::cout << value << " ";
    print(args...);
  }
}

#endif /* _BUILTIN_HH */

