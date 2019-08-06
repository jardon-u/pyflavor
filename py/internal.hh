#ifndef _INTERNAL_HH
# define _INTERNAL_HH

# include <tuple>
# include <type_traits>
# include <utility>
# include <type_traits>

// std::index_sequence might not be defined if libstdc++ is too old, regardless of the compiler version
# if !defined(__cpp_lib_integer_sequence) || (__cpp_lib_integer_sequence < 201304)
// copied from GCC master branch
namespace std
{
  /// Class template integer_sequence
  template<typename _Tp, _Tp... _Idx>
  struct integer_sequence
  {
    typedef _Tp value_type;
    static constexpr size_t size() { return sizeof...(_Idx); }
  };

  template<typename _Tp, _Tp _Num,
	   typename _ISeq = typename std::_Build_index_tuple<_Num>::__type>
  struct _Make_integer_sequence;

  template<typename _Tp, _Tp _Num,  size_t... _Idx>
  struct _Make_integer_sequence<_Tp, _Num, _Index_tuple<_Idx...>>
  {
    static_assert( _Num >= 0, "Cannot make integer sequence of negative length" );

    typedef integer_sequence<_Tp, static_cast<_Tp>(_Idx)...> __type;
  };

  /// Alias template make_integer_sequence
  template<typename _Tp, _Tp _Num>
  using make_integer_sequence
  = typename _Make_integer_sequence<_Tp, _Num>::__type;

  /// Alias template index_sequence
  template<size_t... _Idx>
  using index_sequence = integer_sequence<size_t, _Idx...>;

  /// Alias template make_index_sequence
  template<size_t _Num>
  using make_index_sequence = make_integer_sequence<size_t, _Num>;

  /// Alias template index_sequence_for
  template<typename... _Types>
  using index_sequence_for = make_index_sequence<sizeof...(_Types)>;
} // end of namespace

# endif // end of !defined(__cpp_lib_integer_sequence) || (__cpp_lib_integer_sequence < 201304)


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

  template <typename Tuple, typename Pred>
  constexpr bool any_of_impl(Tuple const&, Pred&&, std::index_sequence<>) {
    return false;
  }

  template <typename Tuple, typename Pred, size_t first, size_t... is>
  constexpr bool any_of_impl(const Tuple& t, Pred&& pred, std::index_sequence<first, is...>) {
    return pred(std::get<first>(t)) || any_of_impl(t, std::forward<Pred>(pred), std::index_sequence<is...>{});
  }

  template <typename... Elements, typename Pred, size_t... is>
  constexpr bool any_of(const std::tuple<Elements...>& t, Pred&& pred) {
    return any_of_impl(t, std::forward<Pred>(pred), std::index_sequence_for<Elements...>{});
  }
} // end of namespace py

#endif /* _INTERNAL_HH */
