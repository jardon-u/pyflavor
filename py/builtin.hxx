#include <list>
#include <tuple>
#include <algorithm>

namespace py
{
  /// Zip N lists
  std::list<std::tuple<>> zip() {
    return {};
  }

  template <typename ...T>
  std::list<std::tuple<T...>> zip(std::list<T>... lst)
  {
    std::list<std::tuple<T...>>  result;
    for (int i = 0, e = std::min({lst.size()...}); i != e; i++) {
      result.emplace_back(std::move(lst.front())...);
      [](...){} ((lst.pop_front(), 0)...);
    }
    return result;
  }

}
