// https://a4z.noexcept.dev/blog/2026/04/13/pmr-generator.html
// g++ 14.1 ; clang 19.1.0
#include <array>
#include <generator>
#include <iostream>
#include <memory_resource>
#include <ranges>
#include <utility>

// The generator signature, using std::allocator_arg_t and
// polymorphic_allocator<> as the first two parameters. Any parameters the
// function itself needs follow.
std::pmr::generator<long> fibonacci(std::allocator_arg_t,
                                    std::pmr::polymorphic_allocator<>,
                                    long base)  //: pre (base == 0 || base == 1)
{
  long a = base;
  long b = 1;
  while (true) {
    co_yield a;
    a = std::exchange(b, a + b);
  }
}

int main() {
  // A 256-byte stack array which feeds a monotonic_buffer_resource. We use
  // null_memory_resource(), which throws std::bad_alloc if the buffer runs out
  // of memory A polymorphic_allocator wraps the resource and is passed to the
  // generator.
  alignas(std::max_align_t) std::array<std::byte, 256> buf;
  std::pmr::monotonic_buffer_resource arena(buf.data(), buf.size(),
                                            std::pmr::null_memory_resource());
  std::pmr::polymorphic_allocator<> alloc{&arena};

  long sum = 0;
  // Using the generator as a range. No surprise here.
  for (long x :
       fibonacci(std::allocator_arg, alloc, 0) | std::views::take(20)) {
    sum += x;
  }

  std::cout << "Sum of first 20 (base 0): " << sum << '\n';
}
