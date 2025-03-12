#include <algorithm>
#include <format>
#include <future>
#include <iostream>
#include <numeric>
#include <thread>
#include <vector>

using namespace std;

void work(const vector<int> &data, promise<int> p) {
  p.set_value(reduce(data.cbegin(), data.cend(), 0));
}

int work(const vector<int> &data) {
  return reduce(data.cbegin(), data.cend(), 0);
}

int main() {
  vector data{0, 1, 2, 3};
  {
    promise<int> p{};
    auto f{p.get_future()};
    jthread t{static_cast<void (*)(const vector<int> &, promise<int>)>(work),
              cref(data), std::move(p)};
    cout << "Sum = " << f.get() << endl;
  }
  {
    packaged_task task{static_cast<int (*)(const vector<int> &)>(work)};
    auto f{task.get_future()};
    jthread t{std::move(task), cref(data)};
    cout << "Sum = " << f.get() << endl;
  }
  {
    auto f{async(static_cast<int (*)(const vector<int> &)>(work), cref(data))};
    cout << "Sum = " << f.get() << endl;
  }
}
