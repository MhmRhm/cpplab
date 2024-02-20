#include <deque>
#include <vector>

template <typename Element,
          template <typename T, typename Allocator = std::allocator<T>>
          class Container = std::deque>
class Wrapper final {
public:
  void include(const Element &t) { container.push_back(t); }
  void includeFront(const Element &t) { container.push_front(t); }

private:
  Container<Element> container{};
};

int main() {
  using namespace std;
  Wrapper<int, vector> wrapper;

  // selective instantiation
  wrapper.include(10);
}
// explicit template instantiations
template class Wrapper<int, std::deque>;
// template class Wrapper<int, std::vector>;
