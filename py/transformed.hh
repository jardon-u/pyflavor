#ifndef _TRANSFORMED_HH
# define _TRANSFORMED_HH

namespace py
{
  template <typename I, typename F>
  struct transformed_iterator
  {
    I iter_;
    F f_;

    transformed_iterator(I iter, F f)
      : iter_(iter), f_(f)
    {
    }

    decltype(f_(*iter_)) operator*()  { return f_(*iter_); }
    transformed_iterator& operator++() { ++iter_; return *this; }
    transformed_iterator operator++(int) { auto orig = *this; ++(*this); return orig; }
  };

template <typename T, typename F>
  struct helper_ {
typedef transformed_iterator<typename T::iterator, F> iterator;
  };

  template <typename T, typename F>
  struct transformed_range : public range< helper_<T,F> >
  {
    //typedef typename T::iterator range_iterator;
    typedef transformed_iterator<typename T::iterator, F> iterator;

    transformed_range(T& r, F f)
    //: begin_(r.begin(), f), end_(r.end(), f)
      : range< helper_<T,F> >(iterator(r.begin(), f),
                                        iterator(r.end(), f))
    {
    }

    //iterator begin() { return begin_; };
    //iterator end() { return end_; };

    //iterator being_;
    //iterator end_;
  };

  template <typename T, typename F>
  transformed_range<T,F> transformed(T& range, F f)
  {
    return transformed_range<T,F>(range, f);
  }
}

#endif /* _TRANSFORMED_HH */

