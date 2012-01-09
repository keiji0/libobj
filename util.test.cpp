int main () {
  TEST(obj::OR(0, 20) == 20);
  
  char *str = NULL;
  TEST(obj::equal(obj::OR<char*>(str, "abcc"), "abcc"));

  Functor(int, (int a), return a) foo;
  TEST(foo(20) == 20);

  Functor(int, (int a), return a * a) bar;
  TEST(bar(20) == 400);
}
