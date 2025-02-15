// https://www.cppstories.com/2024/chrono_dates_zones/
// https://godbolt.org/z/K6b6bsjoj
// -std=c++23

#include <chrono>
#include <print>

int main() {
  const auto now = std::chrono::system_clock::now();
  auto zt_local = std::chrono::zoned_time{std::chrono::current_zone(), now};
  std::print("now is {} UTC and local is: {}\n", now, zt_local);

  constexpr std::string_view Warsaw{"Europe/Warsaw"};
  constexpr std::string_view NewYork{"America/New_York"};
  constexpr std::string_view Tokyo{"Asia/Tokyo"};

  try {
    const std::chrono::zoned_time zt_w{Warsaw, now};
    std::print("Warsaw: {0:%F} {0:%R}\n", zt_w);
    const std::chrono::zoned_time zt_ny{NewYork, now};
    std::print("New York: {0:%F} {0:%R}\n", zt_ny);
    const std::chrono::zoned_time zt_t{Tokyo, now};
    std::print("Tokyo: {0:%F} {0:%R}\n", zt_t);
  } catch (std::runtime_error& ex) {
    std::print("Error: {}", ex.what());
  }

  return 0;
}
