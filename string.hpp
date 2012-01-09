#ifndef OBJ_STRING_HPP
#define OBJ_STRING_HPP

#include <cstring>
#include <cctype>
#include <string>

namespace obj
{

  extern const char hex2char_table[];
  extern const unsigned char char2hex_table[];

  char* trim (char* str);
  bool isalnum (const char *str);
  bool isalpha (const char *str);
  bool isdigit (const char *str);

  inline bool empty (const char* str)
  {
    return str ? *str == '\0' : true;
  }

  inline bool equal(const char* s, const char* ss) {
    return (*s == *ss) ? !std::strcmp(s, ss) : false;
  }

  struct cless {
    bool operator() (const char* t, const char* tt) {
      return (t == tt) ? false :
        (std::strcmp(t, tt) < 0) ? true : false;
    }
  };

  inline char hex2char (unsigned char hex) {
    return hex2char_table[hex];
  }

  inline unsigned char char2hex (unsigned char c) {
    return char2hex_table[c];
  }

  inline unsigned char char2hex (unsigned char c, unsigned char cc) {
    return (char2hex(c) << 4) + char2hex(cc);
  }

  inline char* copy (char* dest, const char *src, std::size_t len) {
    return (char*)std::memcpy(dest, src, len);
  }

  inline char* copy (char* dest, const char *src) {
    return copy(dest, src, strlen(src));
  }

  inline char* copy (const char* src, std::size_t len) {
    return copy(new char[len], src, len);
  }

  inline char* copy (const char* src) {
    return copy(src, std::strlen(src)+1);
  }

  inline char* skip (char* str, char c) {
    return *str ? ((*str == c) ? skip(++str, c) : str) : str;
  }

  inline char* append (char* dest, const char* src, std::size_t n) {
    copy(dest, src, n);
    return dest + n;
  }

  inline char* append (char* dest, const char* src) {
    return (append(dest, src, strlen(src) + 1) - 1);
  }

  inline void replace (char *str, char x, char y) {
    for (; *str; str++) if (*str == x) *str = y;
  }
}

#endif
