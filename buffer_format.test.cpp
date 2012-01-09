#include <vector>
#include <obj/time.hpp>

int main ()
{
  {
    obj::Buffer buf;
    buf << F::hex<char>('f');
    TEST(obj::equal(buf.str(), "66"));
  }
  {
    obj::Buffer buf;
    std::vector<int> vec;
    vec.push_back(20);
    vec.push_back(30);
    buf << F::concat<std::vector<int> >(", ", vec);
    TEST(obj::equal(buf.str(), "20, 30"));
  }
  {
    obj::Buffer buf;
    std::vector<const char*> vec;
    vec.push_back("bar");
    vec.push_back("hoge");
    buf << F::concat<std::vector<const char*> >(", ", vec);
    TEST(obj::equal(buf.str(), "bar, hoge"));
  }
  {
    {
      obj::Buffer buf;
      buf << F::string("abc");
      TEST(obj::equal(buf.str(), "\"abc\""));
    }
    {
      obj::Buffer buf;
      buf << F::string("a\"c");
      TEST(obj::equal(buf.str(), "\"a\\\"c\""));
    }
    {
      obj::Buffer buf;
      buf << F::string("aa\\");
      TEST(obj::equal(buf.str(), "\"aa\\\\\""));
    }
//     {
//       obj::Buffer buf;
//       TIMEC(100000, {
//           const char* s = "abcdefg";
//           buf << '"';
//           while (char c = *s++) {
//             switch (c) {
//             case '"':  buf.write("\\\"", 2); break;
//             case '\\': buf.write("\\\\", 2); break;
//             default:   buf.write(c);
//             }
//           }
//           buf << '"';
//         });
//     }
//     {
//       obj::Buffer buf;
//       TIMEC(100000, buf << F::string("aa\\"));
//     }
  }
//   {
//     obj::Buffer buf;
//     std::vector<const char*> vec;
//     vec.push_back("bar");
//     vec.push_back("hoge");
//     vec.push_back("foo");
//     TIMEC(100000, buf << F::concat<std::vector<const char*> >(", ", vec));
//   }
//   {
//     obj::Buffer buf;
//     std::vector<const char*> vec;
//     vec.push_back("bar");
//     vec.push_back("hoge");
//     vec.push_back("foo");
//     TIMEC(100000, {
//         for (std::vector<const char*>::iterator it = vec.begin();;) {
//           buf << *(it++);
//           if (vec.end() == it) break;
//           else buf << ", ";
//         }
//       });
//   }
}
