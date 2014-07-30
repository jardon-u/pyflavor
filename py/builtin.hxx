#include <list>
#include <tuple>
#include <algorithm>
#include <boost/iterator/zip_iterator.hpp>
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
