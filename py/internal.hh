#ifndef _INTERNAL_HH
# define _INTERNAL_HH

# include <tuple>
# include <type_traits>
# include <utility>

# define GENERATE_HAS_MEMBER(member)                                    \
  template < class T >                                                  \
  class HasMember_##member                                              \
  {                                                                     \
  private:                                                              \
    using Yes = char[2];                                                \
    using  No = char[1];                                                \
                                                                        \
    struct Fallback { int member; };                                    \
    struct Derived : T, Fallback { };                                   \
                                                                        \
    template < class U >                                                \
      static No& test ( decltype(U::member)* );                         \
    template < typename U >                                             \
      static Yes& test ( U* );                                          \
                                                                        \
  public:                                                               \
    static constexpr bool RESULT                                        \
      = sizeof(test<Derived>(nullptr)) == sizeof(Yes);                  \
  };                                                                    \
                                                                        \
  template < class T >                                                  \
  struct has_member_##member                                            \
   : public std::integral_constant<bool, HasMember_##member<T>::RESULT> \
   { };                                                                 \

namespace py
{
  namespace internal
  {
    GENERATE_HAS_MEMBER(begin)
    GENERATE_HAS_MEMBER(end)

    // :(
    template<typename T>
    struct is_callable
    {
    private:
      typedef char(&yes)[1];
      typedef char(&no)[2];

      struct Fallback { void operator()(); };
      struct Derived : T, Fallback { };

      template<typename U, U> struct Check;

      template<typename>
      static yes test(...);

      template<typename C>
      static no test(Check<void (Fallback::*)(), &C::operator()>*);

    public:
      static const bool value = sizeof(test<Derived>(0)) == sizeof(yes);
    };
  }

  template<int ...>
  struct seq { };

  template<int N, int ...S>
  struct gens : gens<N-1, N-1, S...> { };

  template<int ...S>
  struct gens<0, S...> {
    typedef seq<S...> type;
  };


  template<typename Function, typename Tuple, size_t ... I>
  auto apply(Function f, Tuple t, std::index_sequence<I ...>)
  {
    return f(std::get<I>(t) ...);
  }

  template<typename Function, typename Tuple>
  auto apply(Function f, Tuple t)
  {
    static constexpr auto size = std::tuple_size<Tuple>::value;
    return apply(f, t, std::make_index_sequence<size>{});
  }
}

#endif /* _INTERNAL_HH */
