// https://godbolt.org/z/81fMxv3Go
// -std=c++23 -fsanitize=undefined

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <utility>
#include <vector>

#ifdef _MSC_VER
#include <crtdbg.h>
#endif

struct Color {
  std::uint8_t r, g, b, a;
};

// Assume that only restricted set of texture caps is supported.
void generate_texture(std::vector<Color>& tex, std::size_t xy) {
  switch (xy) {
    case 128:
      [[fallthrough]];
    case 256:
      [[fallthrough]];
    case 512: /* ... */
      tex.clear();
      tex.resize(xy * xy, Color{0, 0, 0, 0});
      break;
    default:
      std::unreachable();
  }
}

int main() {
#ifdef _MSC_VER
  _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
  _CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDERR);
#endif
  std::vector<Color> tex;
  generate_texture(tex, 128);  // OK
  assert(tex.size() == 128 * 128);
  std::cout << "OK: 128\n";

  generate_texture(tex, 32);  // Results in undefined behavior
  return EXIT_FAILURE;
}
