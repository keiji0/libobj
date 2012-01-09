#ifndef OBJ_TYPE_HPP
#define OBJ_TYPE_HPP

#include <cstddef>
#include <obj/util.hpp>

namespace obj
{
  typedef char byte;
  typedef const char* cchar;
  typedef void* pointer;

  template <typename T> struct T2T
  {
    typedef T original_type;
  };

  template <typename T> struct Type
  {
    T val;
    Type (T v): val(v) {};
    operator T (void) const { return val; }
  };
}

#endif
