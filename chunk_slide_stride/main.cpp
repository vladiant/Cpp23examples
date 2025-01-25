#include <print>
#include <ranges>
#include <vector>

int main() {
  std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9};

  // Chunk: divide the range into groups of 3
  auto chunks = std::views::chunk(numbers, 3);
  std::println("Chunks of 3:");
  for (const auto& chunk : chunks) {
    for (int n : chunk) std::print("{} ", n);
    std::println("");
  }

  // Slide: create overlapping subranges of size 3
  auto sliding = std::views::slide(numbers, 3);
  std::println("\nSliding Window of 3:");
  for (const auto& window : sliding) {
    for (int n : window) std::print("{} ", n);
    std::println("");
  }

  // Stride: skip every 2 elements
  auto strided = std::views::stride(numbers, 2);
  std::println("\nStrided Range (step 2):");
  for (int n : strided) std::print("{} ", n);
}
