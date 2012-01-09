#include <obj/time.hpp>

using namespace std;
using namespace obj;

int main ()
{
  {
    Buffer buf(200);
  
    TEST(buf.size() == 0);
    TEST(buf.max_size() == 200);
  
    buf << 'a' << "b";
    TEST(buf.size() == 2);
    TEST(equal(buf.str(), "ab"));
    TEST(buf.size() == 2);
    buf.clear();
    
    buf << "abc";
    TEST(equal(buf.str(), "abc"));
    buf.clear();
  }
  {
    Buffer buf;
    buf << "abcdef,";
    buf.seek(-1);
    buf << '\0';
    TEST(obj::equal(buf.str(), "abcdef"));
  }
}
