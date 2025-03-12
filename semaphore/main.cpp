#include <chrono>
#include <iostream>
#include <semaphore>
#include <syncstream>
#include <thread>
#include <vector>

using namespace std;

counting_semaphore execution_semaphore{4};

void worker(int id) {
  execution_semaphore.acquire();
  for (size_t i{}; i < 5; i += 1) {
    std::osyncstream(std::cout) << "Thread " << id << " is executing\n";
    std::this_thread::sleep_for(1s);
  }
  execution_semaphore.release();
}

int main() {
  std::vector<std::jthread> threads;
  for (int i{}; i < 10; i += 1) {
    threads.emplace_back(worker, i);
  }
  return 0;
}
