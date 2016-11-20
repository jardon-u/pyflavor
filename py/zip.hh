#ifndef _ZIP_HH
# define _ZIP_HH

# include <iterator>
# include <tuple>
# include "range.hh"
# include "predicate.hh"

namespace py
{
  namespace {
    template <typename... Iter>
    struct zip_iterator
    {
      using value_type = std::tuple<typename std::iterator_traits<Iter>::value_type...>;

      zip_iterator(const Iter& ...iters)
      {
        _iterators = std::tuple<Iter...>(iters...);
      }

      value_type operator*() { return  }

      zip_iterator& operator++()
      {

        return *this;
      }
      zip_iterator operator++(int)
      {
        auto orig = *this; ++(*this); return orig;
      }
      bool operator!=(const zip_iterator& x)
      {
        return _iterators != x._iterators;
      }
      bool operator==(const zip_iterator& x)
      {
        return _iterators == x._iterators;
      }

      std::tuple<Iter...> _iterators;
    };
  }

  template <typename ...Container>
  auto zip(const Container&... containers)
  {
    typedef zip_iterator<typename Container::iterator...> iterator;
    return py::range<iterator>(iterator(begin(containers)...),
                               iterator(end(containers)...));
  }
}

#endif /* _ZIP_HH */
