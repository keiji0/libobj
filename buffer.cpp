#include <obj/buffer.hpp>

namespace obj
{
  void Buffer::resize (std::size_t new_size) {
    char *new_begin = new char[new_size];
    std::size_t offset = (size() > new_size) ? new_size : size();

    memcpy(new_begin, begin_, offset);
    delete[] begin_;

    begin_ = new_begin;
    current_ = begin_ + offset;
    end_ = begin_ + new_size;
  }

  void Buffer::clear () {
    delete[] begin_;
    begin_ = new char[DEFAULT_SIZE];
    current_ = begin_;
    end_ = begin_ + DEFAULT_SIZE;
  }
}
