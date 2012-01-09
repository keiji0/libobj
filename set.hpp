#ifndef OBJ_SET_HPP
#define OBJ_SET_HPP

#include <set>

namespace obj
{
  template <class T> inline std::set<T>& operator<< (std::set<T>& s, T& t) {
    s.insert(t);
    return s;
  }
}

#endif
