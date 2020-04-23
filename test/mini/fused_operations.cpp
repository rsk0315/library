#define IGNORE
// @ignore

#include <cassert>
#include <climits>
#include <iomanip>
#include <iostream>

#include "integer/fused_operations.cpp"

#define test_assert(expr, expected) do {                        \
    auto found = expr;                                          \
    std::cerr << std::setw(64) << std::setfill('-') << "\n";    \
    std::cerr << "expr:     " << #expr << '\n';                 \
    std::cerr << "found:    " << found << '\n';                 \
    std::cerr << "expected: " << expected << '\n';              \
    std::cerr << std::setw(64) << std::setfill('-') << "\n";    \
    assert(found == expected);                                  \
  } while (false)

int main() {
  test_assert(fused_mul_add(65536, 32768, -1), 2147483647);
  test_assert(fused_add_mod(1000, 1000, 900), 200);
  test_assert(fused_add_mod(2000000000, 2000000000, 2100000000), 1900000000);
  test_assert(fused_mul_mod(1000000, 1000000, 998244353), 757402647);

  test_assert(fused_mul_mod(+1000000000, +1000000000, +1000000007), 49);
  test_assert(fused_mul_mod(+1000000000, +1000000000, -1000000007), -999999958);
  test_assert(fused_mul_mod(+1000000000, -1000000000, +1000000007), 999999958);
  test_assert(fused_mul_mod(+1000000000, -1000000000, -1000000007), -49);
  test_assert(fused_mul_mod(-1000000000, +1000000000, +1000000007), 999999958);
  test_assert(fused_mul_mod(-1000000000, +1000000000, -1000000007), -49);
  test_assert(fused_mul_mod(-1000000000, -1000000000, +1000000007), 49);
  test_assert(fused_mul_mod(-1000000000, -1000000000, -1000000007), -999999958);

  test_assert(fused_add_mod(2, 3, +5), 0);
  test_assert(fused_add_mod(2, 3, -5), 0);

  test_assert(fused_mul_mod(+3, +4, +2), 0);
  test_assert(fused_mul_mod(+3, +4, -2), 0);
  test_assert(fused_mul_mod(+3, -4, +2), 0);
  test_assert(fused_mul_mod(+3, -4, -2), 0);
  test_assert(fused_mul_mod(-3, +4, +2), 0);
  test_assert(fused_mul_mod(-3, +4, -2), 0);
  test_assert(fused_mul_mod(-3, -4, +2), 0);
  test_assert(fused_mul_mod(-3, -4, -2), 0);

  test_assert(fused_mul_mod(INT_MIN, -1, -1), 0);
  test_assert(fused_mul_mod(INT_MIN, +1, -1), 0);
  test_assert(fused_mul_mod(INT_MIN, -1, +1), 0);
  test_assert(fused_mul_mod(INT_MIN, +1, +1), 0);

  test_assert(fused_mul_min(1000000000, 1000000000, 2000000000), 2000000000);
  test_assert(fused_mul_min(1000, 1000, 2000000000), 1000000);
  test_assert(fused_mul_min(100, -100, 0), -10000);
  test_assert(fused_mul_min(-100, -100, 0), 0);
}
