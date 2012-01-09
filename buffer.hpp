#ifndef OBJ_BUFFER_HPP
#define OBJ_BUFFER_HPP

#include <cstdio>
#include <ostream>
#include <sstream>
#include <iostream>

#include <obj/util.hpp>
#include <obj/string.hpp>

namespace obj
{ 
  class Buffer : NonCopy
  {
  PRIVATE:
    char* begin_;
    char* current_;
    char* end_;
    
  PUBLIC:
    enum { EXTEND_NUMBER = 2 };
    enum { DEFAULT_SIZE = 4096 };
    
    Buffer (std::size_t size = DEFAULT_SIZE)
      : begin_(new char[size]), current_(begin_), end_(begin_ + size) {
    }
    
    ~Buffer () {
      delete [] begin_;
    }
    
  PRIVATE:
    void resize (std::size_t s);
    
    void extend (std::size_t s) {
      resize(max_size() * EXTEND_NUMBER + s);
    }
    
    bool fillp (std::size_t len) const {
      return (current_ + len) > end_;
    }

    void update (std::size_t len) {
      if (fillp(len)) extend(len);
    }
    
  PUBLIC:
    void clear () ;

    std::size_t size () const {
      return current_ - begin_;
    }
    
    std::size_t max_size () const {
      return end_ - begin_;
    }

    Buffer& write (const char* str, int len) {
      update(len);
      memcpy(current_, str, len);
      current_ += len;
      return *this;
    }

    Buffer& write (const char* str) {
      return write(str, strlen(str));
    }

    Buffer& write (const char c) {
      update(1);
      *current_ = c;
      current_++;
      return *this;
    }

    void flush (int fd = STDOUT_FILENO) const {
      ::write(fd, begin_, size());
    }

    const char* str () {
      *current_ = '\0';
      return begin_;
    }

    void seek (int s) {
      current_ = current_ + s;
    }
  };
}

#include <obj/buffer_format.hpp>

#endif
