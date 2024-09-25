// https://godbolt.org/z/qPKac6eYf

#include <iostream>

struct Test {
  template <typename Self>
  void explicitCall(this Self&& self, const std::string& text) {  // (9)
    std::cout << text << ": ";
    std::forward<Self>(self).implicitCall();  // (10)
    std::cout << '\n';
  }

  void implicitCall() & {  // (1)
    std::cout << "non const lvalue";
  }

  void implicitCall() const& {  // (2)
    std::cout << "const lvalue";
  }

  void implicitCall() && {  // (3)
    std::cout << "non const rvalue";
  }

  void implicitCall() const&& {  // (4)
    std::cout << "const rvalue";
  }
};

int main() {
  std::cout << '\n';

  Test test;
  const Test constTest;

  test.explicitCall("test");                                 // (5)
  constTest.explicitCall("constTest");                       // (6)
  std::move(test).explicitCall("std::move(test)");           // (7)
  std::move(constTest).explicitCall("std::move(consTest)");  // (8)

  std::cout << '\n';
}
