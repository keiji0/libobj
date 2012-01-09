#ifndef OBJ_ALGORITHM_HPP
#define OBJ_ALGORITHM_HPP

namespace obj {
  
  template <class P, class S> inline bool every (P pred, S &s)
  {
    for (typename S::iterator it = s.begin(); it != s.end(); it++)
      if (!pred(*it)) return false;
    return true;
  }
  
  template <class P, class S> inline bool any (P pred, S &s)
  {
    for (typename S::iterator it = s.begin(); it != s.end(); it++)
      if (pred(*it)) return true;
    return false;
  }
  
}

#endif
