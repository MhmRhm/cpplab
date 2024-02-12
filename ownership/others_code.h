#include <memory>

std::unique_ptr<int> lend_me_this() { return nullptr; }

void delete_this(int *pointer) {}

void borrow_this(std::unique_ptr<int> pointer) {}

void dont_want_this(std::shared_ptr<int> pointer) {}

void can_i_have_it(std::shared_ptr<int> &pointer) {}
