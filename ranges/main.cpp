// https://godbolt.org/z/7er69WcPj

#include <iostream>
#include <ranges>
#include <vector>

std::vector<int> range(int begin, int end, int stepsize = 1) {
  std::vector<int> result{};
  if (begin < end) {  // (5)
    auto boundary = [end](int i) { return i < end; };
    result = std::ranges::views::iota(begin) | std::views::stride(stepsize) |
             std::views::take_while(boundary) | std::ranges::to<std::vector>();
  } else {  // (6)
    begin++;
    end++;
    stepsize *= -1;
    auto boundary = [begin](int i) { return i < begin; };
    result = std::ranges::views::iota(end) | std::views::take_while(boundary) |
             std::views::reverse | std::views::stride(stepsize) |
             std::ranges::to<std::vector>();
  }
  return result;
}

int main() {
  std::cout << std::endl;

  // range(1, 50)                                 // (1)
  auto res = range(1, 50);
  for (auto i : res) std::cout << i << " ";

  std::cout << "\n\n";

  // range(1, 50, 5)                              // (2)
  res = range(1, 50, 5);
  for (auto i : res) std::cout << i << " ";

  std::cout << "\n\n";

  // range(50, 10, -1)                           // (3)
  res = range(50, 10, -1);
  for (auto i : res) std::cout << i << " ";

  std::cout << "\n\n";

  // range(50, 10, -5)                           // (4)
  res = range(50, 10, -5);
  for (auto i : res) std::cout << i << " ";

  std::cout << "\n\n";
}
