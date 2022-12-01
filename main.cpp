#include <functional>
#include <taskflow/taskflow.hpp>
#include <thread>
#include <vector>

#include "dbg_out.h"

void print1(size_t job_id) {
  dbg_out("Executing", "job", job_id, "from", "print1()");
}
void print2(size_t job_id) {
  dbg_out("Executing", "job", job_id, "from", "print2()");
}
void print3(size_t job_id) {
  dbg_out("Executing", "job", job_id, "from", "print3()");
}

int main() {
  static constexpr size_t num_jobs = 100'000;

  tf::Executor ex;
  tf::Taskflow tf;

  for (size_t i = 0; i < num_jobs; ++i) {
    tf.emplace([i]() { print1(i); });
    tf.emplace([i]() { print2(i); });
    tf.emplace([i]() { print3(i); });
  }

  ex.run(tf).wait();

  return 0;
}
