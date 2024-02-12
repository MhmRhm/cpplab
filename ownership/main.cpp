#include <iostream>
#include <memory>

#include "others_code.h"

int main() {
  using namespace std;

  auto uptr{lend_me_this()};
  borrow_this(move(uptr));
  // delete_this(uptr.get());

  auto sptr{make_shared<int>(0)};
  dont_want_this(sptr);
  // can_i_have_it(sptr);
}
