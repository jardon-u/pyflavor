#ifndef _FD_HH
# define _FD_HH

# include <boost/range.hpp>
#include <fstream>
#include <iterator>
#include <stdexcept>
#include <memory>

namespace py
{

  class fd
  {
  public:

    class line : public std::string
    {
      friend std::istream& operator>>(std::istream& is, line& line)
      {
        return std::getline(is, line);
      }
    };

    std::unique_ptr<std::ifstream> is = std::unique_ptr<std::ifstream>(new std::ifstream);

    typedef std::istream_iterator<line> line_iterator;

    typedef std::string type;

    fd(const std::string& fn, const std::ios_base::openmode& modes)
    {
      is->open(fn, modes);
      if (!is->is_open())
        throw std::runtime_error("File not found: " + fn);
    }

    line_iterator begin()
    {
      return line_iterator(*is);
    }

    line_iterator end()
    {
      return line_iterator();
    }

    line_iterator begin() const
    {
      return line_iterator(*is);
    }

    line_iterator end() const
    {
      return line_iterator();
    }
  };

}


namespace boost
{
  template<>
  struct range_iterator<py::fd>
  {
    typedef py::fd::line_iterator type;
  };

  template<>
  struct range_const_iterator<py::fd>
  {
    typedef py::fd::line_iterator type;
  };

    // Overload begin() and end(), both const and non-const versions
  py::fd::line_iterator begin(py::fd & w) { return w.begin(); }
  py::fd::line_iterator end(py::fd & w) { return w.end(); }

  py::fd::line_iterator begin(py::fd const & w) { return w.begin(); }
  py::fd::line_iterator  end(py::fd const & w) { return w.end(); }
}

#endif /* _FD_HH */

