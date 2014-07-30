#ifndef _REDUCE_HH
# define _REDUCE_HH

# include <iterator>

namespace py
{
  template <typename T, typename F>
  auto reduce(F f, const T& c)
  {
    typedef decltype(f(*c.begin(),*c.begin())) result_of_f;
    typedef typename T::const_iterator iterator;

    result_of_f acc = *c.begin();
    for (iterator it = std::next(c.begin()); it != c.end(); it++)
    {
      acc = f(acc, *it);
    }
    return acc;
  }
}

#endif /* _REDUCE_HH */

