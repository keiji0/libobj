#include <vector>

bool odd (int i) { return i % 2;}
bool even (int i) { return !odd(i);}

int main ()
{
  {
    std::vector<int> vec;
    vec.push_back(1);
    vec.push_back(3);
    vec.push_back(5);
    TEST(obj::every(odd, vec));
    vec.push_back(4);
    TEST(!obj::every(odd, vec));
  }
  {
    std::vector<int> vec;
    vec.push_back(1);
    vec.push_back(3);
    vec.push_back(5);
    TEST(obj::any(odd, vec));
    TEST(!obj::any(even, vec));
    vec.push_back(4);
    TEST(obj::any(odd, vec));
  }
}
