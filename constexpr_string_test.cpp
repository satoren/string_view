#include <cassert>
#include <cstring>
#include <iostream>

#if __cplusplus >= 201103L || (defined(_MSC_VER) && _MSC_VER >= 1800)
#include "constexpr_string.hpp"
#endif

int main() {
#if __cplusplus >= 201103L || (defined(_MSC_VER) && _MSC_VER >= 1800)
  using namespace compiletime;

  constexpr auto test = to_constexpr_string("abc");
  constexpr auto test2 = to_constexpr_string("def");
  constexpr auto test3 = test + test2;

  std::string teststr("gh");
  assert(test.to_string() == "abc");
  assert(test3.to_string() == "abcdef");
  assert((test3 + teststr) == "abcdefgh");
  assert((teststr + test3) == "ghabcdef");

  constexpr bool test_compare = (test == test);
  constexpr bool test_compare2 = (test == test2);
  static_assert(test_compare, "");
  static_assert(!test_compare2, "");
#endif
  return 0;
}
