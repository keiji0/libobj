#ifndef GUESS_HPP
#define GUESS_HPP

namespace obj {
  enum CharCode { UTF_8 = 1, SJIS, ISO_2022_JP, EUC_JP };
  inline const char *CharCodeName(CharCode code){
    static const char *t[] = {
      "UTF-8", "SJIS", "ISO-2022-JP", "EUC-JP"
    };
    return t[(int)code-1];
  };
  CharCode guess_jp(const char *buf, int buflen);
}

#endif
