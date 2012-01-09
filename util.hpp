#ifndef OBJ_UTIL_HPP
#define OBJ_UTIL_HPP

#include <cassert>
#include <obj/type.hpp>

#ifdef __TEST__
  #define PRIVATE public
  #define PROTECTED public
#else
  #define PRIVATE private
  #define PROTECTED protected
#endif

#define PUBLIC public

#define __CONCAT__(t, tt) t##tt
#define CONCAT(t, tt) __CONCAT__(t, tt)
#define UNIQUE_NAME(name) CONCAT(name, __LINE__)
#define Functor(ret, args, body) \
  struct UNIQUE_NAME(__Functor__) { ret operator() args { body; } }

namespace obj
{
  template <class T> inline T OR (T t, T tt) {
    return t ? t : tt;
  }

  class NonCopy
  {
  protected:
    NonCopy () {}
    ~NonCopy () {}
  private:
    NonCopy (const NonCopy&);
    const NonCopy& operator= (const NonCopy&);
  };
}

#endif
