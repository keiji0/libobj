#include <obj/buffer.hpp>

int main () {
  using namespace obj;
  
  {
    try {
      ERROR(8, "abc");
    } catch (const obj::Error& error) {
      TEST(error.num == 8);
      TEST(equal(error.message, "abc"));
      TEST(equal(error.file, __FILE__));
    }
  }
}
