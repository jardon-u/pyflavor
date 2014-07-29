#ifndef _TRANSFORMED_HH
# define _TRANSFORMED_HH

# include <boost/range/adaptor/transformed.hpp>
# include <boost/optional/optional.hpp>
namespace py
{

#define RETURNS(...) -> decltype(__VA_ARGS__) { return (__VA_ARGS__); }

  template<class Fun>
  struct function_object
  {
    boost::optional<Fun> f;

    function_object()
    {}
    function_object(Fun f): f(f)
    {}

    function_object(const function_object & rhs) : f(rhs.f)
    {}

    // Assignment operator is just a copy construction, which does not provide
    // the strong exception guarantee.
    function_object& operator=(const function_object& rhs)
    {
      if (this != &rhs)
      {
        this->~function_object();
        new (this) function_object(rhs);
      }
      return *this;
    }

    template<class F>
    struct result
    {};

    template<class F, class T>
    struct result<F(T)>
    {
      typedef decltype(std::declval<Fun>()(std::declval<T>())) type;
    };

    template<class T>
    auto operator()(T && x) const RETURNS((*f)(std::forward<T>(x)))

      template<class T>
      auto operator()(T && x) RETURNS((*f)(std::forward<T>(x)))
      };

  template<class F>
  function_object<F> make_function_object(F f)
  {
    return function_object<F>(f);
  }

  template <typename T>
  auto transformed(const T& f)
    -> decltype(boost::adaptors::transformed(make_function_object(f)))
  {
    return boost::adaptors::transformed(make_function_object(f));
  }
}

#endif /* _TRANSFORMED_HH */

