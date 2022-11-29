// https://godbolt.org/z/WaevozddP
#include "dbg_out.h"
#include <thread>
#include <vector>

void print1() {
  dbg_out("Printing", "from", "print1()");
}
void print2() {
  dbg_out("Printing", "from", "print2()");
}
void print3() {
  dbg_out("Printing", "from", "print3()");
}

int main() {
  static constexpr size_t num_threads = 1000;

  std::vector<std::thread> threads;
  threads.reserve(num_threads);
  for (size_t i = 0; i < num_threads; ++i) {
    threads.emplace_back(print1);
    threads.emplace_back(print2);
    threads.emplace_back(print3);
  }

  for (std::thread &t : threads) {
    t.join();
  }

  return 0;
}
