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

  struct Composit {
    int attr1{1};
    int attr2{2};
  };
  auto composit{make_shared<Composit>()};
  auto alias{shared_ptr<int>{composit, &composit->attr2}};
  cout << *alias << endl;

  class Good : public std::enable_shared_from_this<Good> {
  public:
    std::shared_ptr<Good> getptr() { return shared_from_this(); }
  };

  class Best : public std::enable_shared_from_this<Best> {
    struct Private {};

  public:
    Best(Private) {}
    static std::shared_ptr<Best> create() {
      return std::make_shared<Best>(Private());
    }
    std::shared_ptr<Best> getptr() { return shared_from_this(); }
  };

  struct Bad {
    std::shared_ptr<Bad> getptr() { return std::shared_ptr<Bad>(this); }
  };

  try {
    Good good;
    auto sptr{good.getptr()};
  } catch (const std::exception &e) {
    std::cerr << e.what() << '\n';
  }
}
