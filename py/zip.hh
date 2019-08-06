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
      //FIXME: Is it OK to set the following reference and pointer type ? what about value_type&/* ?
      using reference  = std::tuple<typename std::iterator_traits<Iters>::value_type&...>;
      using pointer    = std::tuple<typename std::iterator_traits<Iters>::value_type*...>;

      zip_iterator(Iters&&... iters)
        : _iterators(std::make_tuple(std::forward<Iters>(iters)...))
      {
        // std::forward is equivalent to { return (is_lvalue_reference<T>::value) ? param : std::move(param); }
        // i.e. if iter is a temporary (rvalue ref) the value get moved to the tuple, copied otherwise

      }

      // return a tuple of non-const references
      //FIXME: make iteration with auto& safe. i.e. store the current tuple
      reference operator*() {
        return get_elements(std::make_index_sequence<sizeof...(Iters)>());
      }

      zip_iterator operator++()
      {
// #if __cplusplus > 201402L // C++1z
//         std::apply([](auto& it) -> std::advance(it, 1), _iterators);
// #elseif
        increment_iterators(std::make_index_sequence<sizeof...(Iters)>());
// #endif
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

      //FIXME: handle zipping containers of different sizes
      bool operator==(const zip_iterator& x)
      {
        return _iterators == x._iterators;
      }

      std::tuple<Iters...> _iterators;

    private:
      template<size_t ...Is>
      reference get_elements(std::index_sequence<Is...>) {
        return std::tie(*std::get<Is>(_iterators)...);
      }

      template<size_t... Is>
      void increment_iterators(std::index_sequence<Is...>) {
#if __cplusplus > 201402L // C++1z
        (++(std::get<Is>(_iterators)), ...);
#else // c++14
        auto l = { (++(std::get<Is>(_iterators)), 0)... };
        (void) l;
#endif
       }
    };
  }

  template <typename... Container>
  auto zip(Container&&... containers)
  {
    // std::decay strips cv-qualifier
    // http://www.cplusplus.com/reference/type_traits/decay/
    typedef zip_iterator<typename std::decay<Container>::type::iterator...> iterator;
    return py::range<iterator>(iterator(std::begin(std::forward<Container>(containers))...),
                               iterator(std::end(std::forward<Container>(containers))...));
  }
}

#endif /* _ZIP_HH */
