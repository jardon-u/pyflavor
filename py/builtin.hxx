#include <list>
#include <tuple>
#include <algorithm>
#include <boost/iterator/zip_iterator.hpp>
#include <boost/range.hpp>

namespace py
{
  /// Make a Zip out of N lists
  template <typename ...T>
  std::list<std::tuple<T...>> zip_new(std::list<T>... lst)
  {
    std::list<std::tuple<T...>>  result;
    struct {
      void operator()(std::list<std::tuple<T...>> &t, int c,
                      typename std::list<T>::iterator ...it) {
        if(c == 0) return;
        t.emplace_back(std::move(*it++)...);
        (*this)(t, c-1, it...);
      }
    } zip;
    zip(result, std::min({lst.size()...}), lst.begin()...);
    return result;
  }
  std::list<std::tuple<>> zip_new() {
    return {};
  }

  // Zip N containers
  template <typename... T>
  auto zip(const T&... containers)
    -> boost::iterator_range<boost::zip_iterator<decltype(boost::make_tuple(std::begin(containers)...))>>
  {
    auto zip_begin = boost::make_zip_iterator(boost::make_tuple(std::begin(containers)...));
    auto zip_end = boost::make_zip_iterator(boost::make_tuple(std::end(containers)...));
    return boost::make_iterator_range(zip_begin, zip_end);
  }
}
