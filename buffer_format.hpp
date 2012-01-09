#ifndef OBJ_FORMAT_HPP
#define OBJ_FORMAT_HPP

#include <obj/buffer.hpp>

namespace F {
#define DEFINE_FORMAT(N) template <typename T> struct N \
  {                                                     \
    const T val;                                        \
    N (const T t): val(t) {};                           \
    operator T (void) const { return val; }             \
  }

  DEFINE_FORMAT(hex);

  template <class S> struct concat {
    const char *sep;
    S &s;
    concat(const char *sep_, S &s_): sep(sep_), s(s_) {}
  };

  struct string {
    const char *v;
    string (const char *v_): v(v_){}
  };
}

namespace obj {

  inline Buffer& operator<< (Buffer& buf, const char* x) {
    return buf.write(x);
  }

  inline Buffer& operator<< (Buffer& buf, const char c) {
    return buf.write(c);
  }

  inline Buffer& operator<< (Buffer& buf, const F::hex<char> hex) {
    char temp[] = { hex2char((hex >> 4) & 15), hex2char(hex & 15) };
    return buf.write(temp, 2);
  }

  inline std::ostream& operator<< (std::ostream& os, Buffer& buf) {
    return os << buf.str();
  }

#define X(TYPE)                                             \
  inline Buffer& operator<< (Buffer& buf, TYPE i) {         \
    std::ostringstream oss;                                 \
    oss << i;                                               \
    return buf << (oss.str()).c_str();                      \
  }
  X(bool);
  X(short);
  X(unsigned short);
  X(int);
  X(unsigned int);
  X(long);
  X(unsigned long);
  X(long long);
  X(unsigned long long)
  X(double);
  X(float);
#undef X

  template <class S> inline obj::Buffer& operator<< (obj::Buffer &buf, F::concat<S> s)
  {
    for (typename S::iterator it = s.s.begin();;) {
      buf << *(it++);
      if (s.s.end() == it) break;
      else buf << s.sep;
    }
    return buf;
  }

  inline obj::Buffer& operator<< (obj::Buffer &buf, F::string s_)
  {
    const char* s = s_.v;
    buf << '"';
    while (char c = *s++) {
      switch (c) {
      case '"':  buf.write("\\\"", 2); break;
      case '\\': buf.write("\\\\", 2); break;
      default:   buf.write(c);
      }
    }
    buf << '"';
    return buf;
  }
}

#endif
