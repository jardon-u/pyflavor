#ifndef _INTERNAL_HH
# define _INTERNAL_HH

# include <tuple>
# include <type_traits>
# include <utility>
# include <type_traits>

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

    // :( Use is_invocable from C++1y ?
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

  template<std::size_t... Ints>
  class index_sequence {
    static constexpr std::size_t size() noexcept { return sizeof...(Ints); }
  };

  template<std::size_t N, std::size_t... S>
  struct make_index_sequence_helper : make_index_sequence_helper<N-1, N-1, S...> {};
  template<std::size_t... S>
  struct make_index_sequence_helper<std::size_t(0), S...> {
    using type = index_sequence<S...>;
  };

  template<std::size_t N>
  using make_index_sequence = typename make_index_sequence_helper<N>::type;

  template<typename...Args>
  using index_sequence_for = make_index_sequence<sizeof...(Args)>;
}

#endif /* _INTERNAL_HH */
