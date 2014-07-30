#include <list>
#include <tuple>
#include <algorithm>
#include <boost/iterator/zip_iterator.hpp>
#include <boost/range.hpp>
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

  // Zip N containers
  template <typename... T>
  inline
  auto zip(const T&... containers)
    -> boost::iterator_range<boost::zip_iterator<decltype(boost::make_tuple(std::begin(containers)...))>>
  {
    auto zip_begin = boost::make_zip_iterator(boost::make_tuple(std::begin(containers)...));
    auto zip_end = boost::make_zip_iterator(boost::make_tuple(std::end(containers)...));
    return boost::make_iterator_range(zip_begin, zip_end);
  }
}
