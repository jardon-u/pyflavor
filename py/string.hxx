#include <string>

namespace py
{

  inline
  template <typename C>
  std::string join(const std::string& separator, const C& container)
  {
    auto begin = std::begin(container);
    auto end = std::end(container);

    std::ostringstream result;
    if (begin != end)
      result << *begin++;
    while (begin != end)
      result << separator << *begin++;
    return result.str();
  }

}
