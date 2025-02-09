// GCC-13.1 https://godbolt.org/z/x371x86hG
#include <format>
#include <iostream>
#include <stacktrace>

class fib_with_stacktrace {
  std::stacktrace::size_type max_depth = 0;
  std::stacktrace max_trace;

 public:
  fib_with_stacktrace() = default;

  // Return the nth number in the fibonaci sequence
  unsigned int fib(unsigned int n) {
    auto trace = std::stacktrace::current();
    auto depth = trace.size();
    if (trace.size() > max_depth) {
      max_trace = trace;
      max_depth = depth;
    }

    return n < 2 ? n : fib(n - 1) + fib(n - 2);
  }

  std::stacktrace get_max_trace() const { return max_trace; }
};

int main(void) {
  fib_with_stacktrace fib_wst;

  for (int i = 0; i < 10; ++i) std::cout << fib_wst.fib(i) << ' ';
  std::cout << '\n';

  const std::stacktrace& trace = fib_wst.get_max_trace();
  std::cout << "Max stack depth was: " << trace.size() << '\n';

  for (const auto& t : trace)
    std::cout << std::format("{}:{} {}\n", t.source_file(), t.source_line(),
                             t.description());
}
