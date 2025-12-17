// https://godbolt.org/z/9z1jvheEM
// -std=c++23 -lstdc++_libbacktrace
// https://godbolt.org/z/neqs9b4Gv -std=c++23 -lstdc++exp
// https://gcc.godbolt.org/z/vhxTxv45d
#include <iostream>
#include <stacktrace>

int nested_func(int c) {
  std::cout << std::stacktrace::current() << '\n';
  return c + 1;
}

int func(int b) { return nested_func(b + 1); }

int main() {
  std::cout << func(777);
  return 0;
}
