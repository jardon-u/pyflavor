#ifndef _BUILTIN_HH
# define _BUILTIN_HH

#include <list>
#include <tuple>
#include <algorithm>
#include <iostream>
#include <utility>

#include "internal.hh"

namespace py
{
  template <typename T, typename... Args>
  void print(const T& value, const Args&... args);

  template <typename... Ts, typename... Args>
  void print(const std::tuple<Ts...>& value, const Args&... args);

  template <class U, typename... Args>
  void print(const std::initializer_list<U>& value, const Args&... args);

  template <class U, typename... Args>
  void print(const std::vector<U>& value, const Args&... args);

  namespace {
    //FIXME: override operator<< for tuple and vectors ?

    template<typename Tuple, size_t... I>
    void print_tuple(const Tuple& t, std::index_sequence<I...>) {
      std::cout << "(";
#if __cplusplus > 201402L // C++1z
      (..., (std::cout << (I == 0? "" : ", "), print(std::get<I>(t))));
#else // c++14
      //FIXME: implement
#endif
      std::cout << ") ";
    }

    template <typename T>
    void print_container(const T& v) {
      using namespace internal;
      static_assert(has_member_begin<T>::value, "c.begin must be defined");
      static_assert(has_member_end<T>::value, "c.end must be defined");
      std::cout << "[";
      for (const auto& e : v)
      {
        print(e);
        //FIXME: handle last element
        std::cout << ", ";
      }
      std::cout << "]";
    }
  }

  //FIXME: make sep and end configurable
  // the duplication below is here to handle printing with new line and not

  /// print
  void println() {
    std::cout << std::endl;
  }

  //tuple
  template <typename... Ts, typename... Args>
  inline
  void println(const std::tuple<Ts...>& value, const Args&... args)
  {
    print_tuple(value, std::make_index_sequence<sizeof...(Ts)>());
    println(args...);
  }

  // one parameter container type
  template <class U, typename... Args>
  inline
  void println(const std::initializer_list<U>& value, const Args&... args)
  {
    print_container(value);
    println(args...);
  }

  template <typename T, typename... Args>
  inline
  void println(const T& value, const Args&... args)
  {
    std::cout << value << " ";
    println(args...);
  }

  /// print ----------------------------------------------------------------
  void print() {
  }

  //tuple
  template <typename... Ts, typename... Args>
  inline
  void print(const std::tuple<Ts...>& value, const Args&... args)
  {
    print_tuple(value, std::make_index_sequence<sizeof...(Ts)>());
    print(args...);
  }

  template <class U, typename... Args>
  inline
  void print(const std::initializer_list<U>& value, const Args&... args)
  {
    print_container(value);
    print(args...);
  }

  template <class U, typename... Args>
  inline
  void print(const std::vector<U>& value, const Args&... args)
  {
    print_container(value);
    print(args...);
  }

  template <template <class, class> class C, class U, class V,
            typename... Args>
  inline
  void print(const C<U, V>& value, const Args&... args)
  {
    print_container(value);
    print(args...);
  }

  template <typename T, typename... Args>
  inline
  void print(const T& value, const Args&... args)
  {
    //FIXME: should not print space when called from print_tuple/container
    //FIXME: print string between quotes
    std::cout << value << " ";
    print(args...);
  }

}

#endif /* _BUILTIN_HH */
