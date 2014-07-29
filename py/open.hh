#ifndef _OPEN_HH
# define _OPEN_HH

# include "fd.hh"

namespace py
{
  auto open(const std::string& fn,
            const std::ios_base::openmode& modes = std::ifstream::in)
    -> fd
  {
    return py::fd(fn, modes);
  }
}

#endif /* _OPEN_HH */

