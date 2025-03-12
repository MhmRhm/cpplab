#include <functional>
#include <iostream>
#include <map>
#include <source_location>
#include <thread>

using namespace std;

using Histogram = map<int, int>;
struct Nums {
  int num1{};
  int num2{};
};
void increment(Nums &nums, Histogram &result) {
  for (size_t i = 0; i < 100'000; i++) {
    nums.num1 = 1, nums.num2 = 10;
    result[nums.num1 + nums.num2]++;
  }
}
class Functor {
public:
  Functor(Nums &nums, Histogram &result) : m_nums{nums}, m_result{result} {}
  void operator()() {
    for (size_t i = 0; i < 100'000; i++) {
      m_nums.num1 = 2, m_nums.num2 = 20;
      m_result[m_nums.num1 + m_nums.num2]++;
    }
  }

private:
  Nums &m_nums;
  Histogram &m_result;
};
class FunClass {
public:
  FunClass(Nums &nums, Histogram &result) : m_nums{nums}, m_result{result} {}
  void increment() {
    for (size_t i = 0; i < 100'000; i++) {
      m_nums.num1 = 3, m_nums.num2 = 30;
      m_result[m_nums.num1 + m_nums.num2]++;
    }
  }

private:
  Nums &m_nums;
  Histogram &m_result;
};

class NoCopyClass {
public:
  NoCopyClass() = default;
  // Not copyable
  NoCopyClass(const NoCopyClass &src) = delete;
  NoCopyClass &operator=(const NoCopyClass &src) = delete;
  // But movable
  NoCopyClass(NoCopyClass &&src) noexcept {};
  NoCopyClass &operator=(NoCopyClass &&src) noexcept {};
  void process() { cout << source_location::current().function_name() << endl; }
  void operator()() const {
    cout << source_location::current().function_name() << endl;
  }
};

int main() {
  Histogram result;
  Nums nums{};

  thread t1{increment, ref(nums), ref(result)};
  thread t2{Functor{nums, result}};
  thread t3{&FunClass::increment, FunClass{nums, result}};
  thread t4{[&] {
    for (size_t i = 0; i < 100'000; i++) {
      nums.num1 = 4, nums.num2 = 40;
      result[nums.num1 + nums.num2]++;
    }
  }};

  t1.join();
  t2.join();
  t3.join();
  t4.join();

  for (auto &[k, v] : result) {
    std::cout << k << " " << v << endl;
  }

  NoCopyClass no_copy_functor{};
  thread t5{cref(no_copy_functor)};
  t5.join();
  thread t6{std::move(no_copy_functor)};
  thread t7{&NoCopyClass::process, NoCopyClass{}};
  t6.join();
  t7.join();
}
