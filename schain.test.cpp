#include <obj/buffer.hpp>

using namespace std;
using namespace obj;

int main () {
  {
    Schain sc;
    sc << "abc" << "fff";
    Buffer buf;
    buf << sc;
    TEST(equal(buf.str(), "abcfff"));
  }
}
