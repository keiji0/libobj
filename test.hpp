#ifndef OBJ_TEST_HPP
#define OBJ_TEST_HPP

#include <cstdlib>
#include <cstdio>
#include <obj/string.hpp>

#define TEST(x)                                                                 \
  if (x) {                                                                      \
    std::printf("%s - %2d, \"%s\" ==> ok\n", __FILE__, __LINE__, #x);           \
  } else {                                                                      \
    std::fprintf(stderr, "%s:%2d: error: %s", __FILE__, __LINE__, #x);          \
    std::exit(1);                                                               \
  }

#define TEST_SECTION(x) \
  std::puts("--- Section " x " start ---")

#endif
