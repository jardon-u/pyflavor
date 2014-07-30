#ifndef _FD_HH
# define _FD_HH

# include <boost/range.hpp>
#include <fstream>
#include <iterator>
#include <stdexcept>
#include <memory>

namespace py
{
  namespace {
    class line : public std::string
    {
      friend std::istream& operator>>(std::istream& is, line& line)
      {
        return std::getline(is, line);
      }
    };
  }

  class fd
  {
    std::unique_ptr<std::ifstream> is = std::unique_ptr<std::ifstream>(new std::ifstream);

  public:
    typedef std::istream_iterator<line> line_iterator;
    typedef std::istream_iterator<const line> line_const_iterator;

    fd(const std::string& fn, const std::ios_base::openmode& modes)
    {
      is->open(fn, modes);
      if (!is->is_open())
        throw std::runtime_error("File not found: " + fn);
    }

    line_iterator begin() { return line_iterator(*is);  }
    line_iterator end()   { return line_iterator();     }
    //line_const_iterator begin() const { return line_const_iterator(*is);  }
    //line_const_iterator end() const   { return line_const_iterator();     }
  };

}

#endif /* _FD_HH */

