// https://godbolt.org/z/ovv3x6EKz

#include <print>
#include <ranges>
#include <vector>

int main() {
  std::vector<int> range1 = {1, 2, 3};
  std::vector<char> range2 = {'A', 'B', 'C'};

  auto product = std::views::cartesian_product(range1, range2);
  std::println("Cartesian Product:");
  for (const auto& [a, b] : product) std::println("({}, {})", a, b);

  auto enumerated = std::views::enumerate(range1);
  std::println("\nEnumerated Range:");
  for (const auto& [index, value] : enumerated)
    std::println("Index: {}, Value: {}", index, value);

  auto zipped = std::views::zip(range1, range2);
  std::println("\nZipped Ranges:");
  for (const auto& [a, b] : zipped) std::println("({}, {})", a, b);
}
