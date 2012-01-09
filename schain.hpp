#ifndef OBJ_SCHAIN_HPP
#define OBJ_SCHAIN_HPP

#include <cstring>

#include <obj/util.hpp>
#include <obj/mpool.hpp>

namespace obj {

  class Schain {
  PUBLIC:
    struct Chain {
      const char* str;
      Chain *next;
      static void* operator new (std::size_t size, mPool& mp) {
        return mp.allocate(size);
      }
      Chain (const char* s, Chain* n = NULL):
        str(s), next(n) {}
    };
  
  PRIVATE:
    mPool mpool_;
    Chain *begin_;
    Chain *end_;
  
  PUBLIC:
    Schain (const char* str = "", std::size_t size = mPool::DEFAULT_SIZE)
      : mpool_(size),
        begin_(new(mpool_) Chain(str, NULL)),
        end_(begin_) {}

    Schain& cons (const char* str) {
      begin_ = new(mpool_) Chain(str, begin_);
      return *this;
    }

    Schain& operator<< (const char* str) {
      end_ = (end_->next = new(mpool_) Chain(str, NULL));
      return *this;
    }

    template <class T> T& operator>> (T& t) {
      Chain *next = begin_;
      do {
        t << next->str;
      } while ((next = next->next));
      return t;
    }

    template <class T> void foreach (T t) {
      Chain *next = begin_;
      do {
        t(next->str);
      } while ((next = next->next));
    }
  };

  inline Schain& operator>> (const char* str, Schain& sc) {
    return sc.cons(str);
  }

  namespace {
    template <class T> struct Foo {
      T& t;
      Foo (T& _t): t(_t) {}
      T& operator() (const char* s) { return t << s; };
    };
    template <class T> T& operator<< (T& t, Schain& s) {
      s.foreach(Foo<T>(t));
      return t;
    }
  }
}

#endif
