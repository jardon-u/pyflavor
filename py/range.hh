#ifndef _RANGE_HH
# define _RANGE_HH

template <typename I>
struct range
{
  typedef typename I::iterator Iter;

  range(Iter begin, Iter end)
    : begin_(begin), end_(end)
  {}

  Iter begin() { return begin_; };
  Iter end() { return end_; };

private:
  Iter begin_;
  Iter end_;
};

#endif /* _RANGE_HH */

