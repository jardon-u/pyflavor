#ifndef _ZIP_HH
# define _ZIP_HH

# include <iterator>
# include <tuple>
# include "range.hh"
# include "predicate.hh"

namespace py
{
  namespace {
    template <typename... Iters>
    struct zip_iterator
    {
      using iterator_category = std::input_iterator_tag;
      using value_type = std::tuple<typename std::iterator_traits<Iters>::value_type...>;
      using reference  = value_type&;
      using pointer    = value_type*;
      using ref_type = std::tuple<typename std::iterator_traits<Iters>::value_type&...>;

      zip_iterator(Iters... iters)
      {
        _iterators = std::make_tuple(iters...);
      }

      // returns a tuple of non-const references
      ref_type operator*() {
        return get_elements(make_index_sequence<sizeof...(Iters)>());
      }

      zip_iterator operator++()
      {
        increment_iterators(make_index_sequence<sizeof...(Iters)>());
        return *this;
      }
      zip_iterator& operator++(int)
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

      std::tuple<Iters...> _iterators;

    private:
      template<size_t ...Is>
      ref_type get_elements(index_sequence<Is...>) {
        return std::tie(*std::get<Is>(_iterators)...);
      }

      template<size_t ...Is>
      void increment_iterators(index_sequence<Is...>) {
         auto l = { (++(std::get<Is>(_iterators)), 0)... };
         (void) l;
       }
    };
  }

  template <typename... Container>
  auto zip(Container&... containers)
  {
    typedef zip_iterator<typename Container::iterator...> iterator;
    return py::range<iterator>(iterator(std::begin(containers)...),
                               iterator(std::end(containers)...));
  }
}

#endif /* _ZIP_HH */
