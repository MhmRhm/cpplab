#pragma once

#include <locale>

struct CommaSeparator : std::ctype<wchar_t> {
  bool do_is(mask m, char_type c) const {
    if ((m & space) && c == L' ') {
      return false;
    }
    if ((m & space) && c == L',') {
      return true;
    }
    return ctype::do_is(m, c);
  }
};
