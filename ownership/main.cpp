#include <iostream>
#include <memory>

#include "others_code.h"

int main() {
  using namespace std;

  auto uptr{lend_me_this()};
  borrow_this(move(uptr));
  // delete_this(uptr.get());

  // Cpp 20
  auto sptr{make_shared_for_overwrite<int>()};
  dont_want_this(sptr);
  // can_i_have_it(sptr);
}
