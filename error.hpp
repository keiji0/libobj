#ifndef OBJ_ERROR_HPP
#define OBJ_ERROR_HPP

#include <iostream>
#include <cerrno>
#include <exception>

namespace obj
{
  inline std::ostream& err_doit (const char *file, unsigned int line) {
    int errno_save = errno;
    std::cerr << file << ": " << line << " -> " << std::strerror(errno_save);
    return std::cerr;
  }

#define ERR_SYS(message) { obj::err_doit(__FILE__, __LINE__) << " --- " << message << std::endl; exit(1); }

  struct Error : std::exception {
    const int num;
    const char* message;
    const char* file;
    const int line;
    Error (int n,  const char* m, const char* f,  int l) :
      num(n), message(m), file(f), line(l) {}
  };

  template <class T> inline T& operator<< (T& t, const Error& e) {
    return t << e.file << ':' << e.line << ": error." << e.num << " -> " << e.message;
  }

#define ERROR(num, mes) throw obj::Error(num, mes, __FILE__, __LINE__)
  
}

#endif
