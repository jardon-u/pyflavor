#ifndef _RANGE_HH
# define _RANGE_HH

# include <algorithm>

namespace py
{
  template <typename Iter>
  struct range
  {
    range(Iter begin, Iter end)
      : begin_(begin), end_(end)
    {}

    Iter begin() { return begin_; };
    Iter end() { return end_; };
    Iter begin() const { return begin_; };
    Iter end() const { return end_; };

  private:
    Iter begin_;
    Iter end_;
  };

  template <typename T, typename U>
  bool operator==(const T& a, const U& b)
  {
    return std::equal(a.begin(), a.end(), b.begin());
  }
}

#endif /* _RANGE_HH */

