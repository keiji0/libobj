#include <obj/type.hpp>
#include <obj/time.hpp>

int main ()
{
  using namespace obj;

  {
    TEST(obj::char2hex('e') == 14);
    TEST(obj::char2hex('3') == 3);
    TEST(obj::char2hex('f') == 15);
    TEST(obj::char2hex('f', 'f') == 255);
  
    TEST(obj::empty(""));
    TEST(obj::empty(NULL));
    TEST(!obj::empty("kk"));

    TEST(obj::equal("abc", "abc"));
    TEST(!obj::equal("abc", "cabc"));

    TEST(cless()("a", "a") == false);
    TEST(cless()("a", "ab") == true);

    char* xxx = obj::copy("abcdefg  ");
    TEST(!std::strcmp(xxx, "abcdefg  "));
    xxx = obj::trim(xxx);
    TEST(!std::strcmp(xxx, "abcdefg"));
  
    TEST(obj::isalnum("abcde8"));
    TEST(!obj::isalnum("abc;de8"));
    TEST(!obj::isalnum(NULL));
    TEST(!obj::isalnum(""));
  
    TEST(!obj::isalpha("abc;de8"));
    TEST(obj::isalpha("abcddddd"));
    TEST(!obj::isalpha(NULL));
    TEST(!obj::isalpha(""));
  
    TEST(obj::isdigit("abcddddd") == false);
    TEST(obj::isdigit("33333") == true);
    TEST(obj::isdigit(NULL) == false);
    TEST(obj::isdigit("") == false);

    TEST(equal(skip(copy("  xxx"), ' '), "xxx"));
  }
  {
    char* first = new char[50];
    char* buf = first;
    buf = append(buf, "ssss");
    TEST(equal(first, "ssss"));
    buf = append(buf, "abcd");
    TEST(equal(first, "ssssabcd"));
    append(append(first, "Foo"), "=Bar");
    TEST(equal(first, "Foo=Bar"));
  }
  {
    char *x = copy("1 2 3 4 5");
    replace(x, ' ', '-');
    TEST(equal(x, "1-2-3-4-5"));
  }
}
