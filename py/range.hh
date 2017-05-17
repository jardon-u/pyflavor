#ifndef _RANGE_HH
# define _RANGE_HH

# include <algorithm>
# include <initializer_list>

namespace py
{
  template <typename Iter>
  struct range
  {
    typedef typename Iter::value_type value_type;

    range(Iter begin, Iter end)
      : begin_(begin), end_(end)
    {}

    Iter begin()       { return begin_; };
    Iter end()         { return end_;   };
    Iter begin() const { return begin_; };
    Iter end() const   { return end_;   };

    template <typename T>
    bool operator==(const T& c)
    {
      return std::equal(begin(), end(), c.begin());
    }

    // todo(ugo) allow len only in this case
    size_t size() const
    {
      size_t s = 0;
      Iter i = begin();
      while (i != end()) {
        ++i; ++s;
      }
      return s;
    }

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
