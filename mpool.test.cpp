using namespace std;

int main ()
{
  obj::mPool mpool(100);

  TEST(mpool.rest() == 100);
  TEST(mpool.chunk_->used() == 0);
  TEST(mpool.length() == 1);

  mpool.allocate(20);
  TEST(mpool.rest() == (100 - 20));
  TEST(mpool.chunk_->used() == 20);

  mpool.allocate(80);
  TEST(mpool.rest() == 0);

  mpool.allocate(30);
  TEST(mpool.rest() == (100 - 30));
  TEST(mpool.length() == 2);

  TEST(obj::equal(mpool.copy("abc"), "abc"));
  TEST(mpool.rest() == (100 - 30 - std::strlen("abc") - 1));
  TEST(mpool.length() == 2);
  TEST(mpool.size() == (20 + 80 + 30 + (std::strlen("abc") + 1)));

  mpool.allocate(150);
  TEST(mpool.rest() == (100 - 30 - std::strlen("abc") - 1));
  TEST(mpool.length() == 3);
  TEST(mpool.size() == (20 + 80 + 30 + (std::strlen("abc") + 1) + 150));
}
