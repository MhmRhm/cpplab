#include <barrier>
#include <iostream>
#include <syncstream>
#include <thread>
#include <vector>

std::barrier sync_barrier(4);

void worker(std::stop_token stopToken, int id) {
  while (!stopToken.stop_requested()) {
    std::osyncstream(std::cout) << "Thread " << id << " is executing\n";
    sync_barrier.arrive_and_wait();
  }
}

int main() {
  std::vector<std::jthread> threads;
  for (int i = 0; i < 3; ++i) {
    threads.emplace_back(worker, i + 1);
  }

  std::string input;
  while (std::cin >> input) {
    sync_barrier.arrive_and_wait();
  }

  for (auto &t : threads) {
    t.request_stop();
  }

  sync_barrier.arrive_and_wait();
  return 0;
}
