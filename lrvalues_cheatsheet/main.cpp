#include <iostream>

struct SomeType {
  int value;
};
void someFuncWithRValueParam(SomeType &&some_object) {}

// lvalue:  has identity and not movable
// xvalue:  has identity and movable
// prvalue: has no identity and movable

// glvalue: has identity (lvalue + xvalue)
// rvalue:  movable (xvalue + prvalue)

int main() {
  // `some_object` is lvalue
  SomeType some_object{};
  // so it can be bound to an lvalue reference
  SomeType &lref{some_object};

  // `std::move(some_object)` is an xvalue
  std::move(some_object);
  // cannot use moved-from object later, so reinitializing it
  some_object = SomeType{};
  // `std::move(some_object)` is an xvalue
  // so it can be bound to an rvalue reference
  SomeType &&xref{std::move(some_object)};

  // `SomeType{42}` is a prvalue
  SomeType{42};
  // so it can be bound to an rvalue reference
  SomeType &&prref{SomeType{42}};

  // `xref` and `prref` are lvalues
  // because they can appear on left side of assignments
  xref = SomeType{420};
  // so the following won't compile
  // someFuncWithRValueParam(xref);
  // we should move from it, then it get compiled
  someFuncWithRValueParam(std::move(xref));
}
