#ifndef OBJ_XML_HPP
#define OBJ_XML_HPP

#include <obj/type.hpp>
#include <obj/buffer.hpp>

namespace F {
  struct xml_str {
    const char* val;
    xml_str (const char* v): val(v) {}
  };

  struct xml_attr {
    const char* key;
    const char* val;
    xml_attr (const char* k, const char* v): key(k), val(v) {}
  };
}

namespace obj
{
  inline Buffer& operator<< (Buffer& buf, F::xml_str xs) {
    const char* s = xs.val;
    while (char c = *s++) {
      switch (c) {
      case '<': buf.write("&lt;", 4); break;
      case '>': buf.write("&gt;", 4); break;
      case '&': buf.write("&amp;", 5); break;
      case '"': buf.write("&quot;", 6); break;
      default:  buf.write(c);
      }
    }
    return buf;
  }

  inline Buffer& operator<< (Buffer& buf, F::xml_attr x) {
    return buf << ' ' << x.key << "=\"" << F::xml_str(x.val) << '"';
  }
}

#endif
