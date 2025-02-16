// https://www.cppstories.com/2024/chrono_dates_zones/
// https://godbolt.org/z/cz8xqfxMz
// -std=c++23

#include <chrono>
#include <print>

void printInfo(std::chrono::sys_days sd, std::string_view zone) {
  auto zt_local =
      std::chrono::zoned_time{"Europe/Warsaw", std::chrono::sys_days{sd}};
  auto info = zt_local.get_info();
  std::print(
      "time info for {:%F} in {}:\nabbrev: {},\nbegin {}, end {}, \noffset {}, "
      "save {}\n",
      sd, zone, info.abbrev, info.begin, info.end, info.offset, info.save);
}

int main() {
  try {
    const auto now = std::chrono::floor<std::chrono::minutes>(
        std::chrono::system_clock::now());
    auto zt_local = std::chrono::zoned_time{"Europe/Warsaw", now};
    std::print("now is {} UTC and Warsaw is: {}\n", now, zt_local);

    auto info = zt_local.get_info();
    std::print(
        "local time info: \nabbrev: {},\n begin {}, end {}, \noffset {}, save "
        "{}\n",
        info.abbrev, info.begin, info.end, info.offset, info.save);
  } catch (std::runtime_error& ex) {
    std::print("Error: {}", ex.what());
  }

  try {
    printInfo(std::chrono::year{2024} / 9 / 14, "Europe/Warsaw");
    printInfo(std::chrono::year{2024} / 11 / 14, "Europe/Warsaw");
  } catch (std::runtime_error& ex) {
    std::print("Error: {}", ex.what());
  }

  return 0;
}
