#include <format>
#include <iostream>
#include <memory>
#include <source_location>

#include "type_erasure.h"

int main() {
  using namespace std;

  struct Deleter1 {
    void operator()(int *ptr) {
      cout << std::source_location::current().function_name() << endl;
      delete ptr;
    }
  };
  struct Deleter2 {
    void operator()(int *ptr) {
      cout << std::source_location::current().function_name() << endl;
      delete ptr;
    }
  };
  {
    shared_ptr<int> ptr1{new int{10}, Deleter1{}};
    shared_ptr<int> ptr2{new int{10}, Deleter2{}};
    ptr1 = ptr2;
  }
  {
    unique_ptr<int, Deleter1> ptr1{new int{10}, Deleter1{}};
    unique_ptr<int, Deleter2> ptr2{new int{10}, Deleter2{}};
    // ptr1 = ptr2;
  }
  {
    struct Plotter1 {
      uint64_t dummy{};
      void operator()(int num) const {
        cout << std::source_location::current().function_name() << endl;
        cout << format("{:_^#20X}", num) << endl;
      }
    };
    struct Plotter2 {
      void operator()(int num) const {
        cout << std::source_location::current().function_name() << endl;
        cout << format("{:_^#20B}", num) << endl;
      }
    };
    Plotable p1{8, Plotter1{}};
    p1.plot();
    Plotable p2{15, Plotter2{}};
    p2.plot();

    p2 = std::move(p1);
    p2.plot();
  }
}
