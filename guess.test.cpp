#include <iconv.h>
#include <iostream>
#include "string.hpp"

int main(){
  const char *src = obj::copy("„Åª„Åí");
  size_t srcSize = strlen(src)+1;
  
  char *dst = new char[1000];
  size_t dstSize = 1000;

  iconv_t ic;
  if ((ic = iconv_open("UTF-8","UTF-8")) < 0) {
    std::cout << "erorr";
    return 0;
  }
  char *dst_buf = dst;
  if (iconv(ic, &src, &srcSize, &dst_buf, &dstSize) < 0) {
    std::cout << "erorr";
    return 0;
  }
  iconv_close(ic);
  
  std::cout << obj::CharCodeName(obj::guess_jp(src,strlen(src)))
            << '(' << src << ") -> "
            << obj::CharCodeName(obj::guess_jp(dst,strlen(dst)))
            << '(' << dst << ')'
            << std::endl;
  
//   TEST(obj::UTF_8 == obj::guess_jp("„Åª„Åí",5));
//   TEST(obj::SJIS == obj::guess_jp("¬ÇŸ¬Ç∞",5));
//   TEST(obj::ISO_2022_JP == obj::guess_jp("$B$[$2(B",5));
//   TEST(obj::EUC_JP == obj::guess_jp("§€§≤",5));
}
