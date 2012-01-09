#include <obj/mpool.hpp>

namespace obj
{
  int mPool::length () const {
    int i;
    Chunk *chunk = chunk_;
    for (i = 0; chunk; i++) chunk = chunk->next;
    return i;
  }

  std::size_t mPool::size () const {
    std::size_t s = 0;
    Chunk *chunk = chunk_;
    while (chunk) {
      s += chunk->used();
      chunk = chunk->next;
    }
    return s;
  }
}
