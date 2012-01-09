#include <obj/time.hpp>

using namespace obj;

int main ()
{
  {
    Buffer buf;
    TEST(equal((buf << F::xml_str("<a")).str(), "&lt;a"));
  }
  {
    Buffer buf;
    buf << F::xml_attr("test", "e< mkkacs");
    std::cout << buf << std::endl;
  }
}
