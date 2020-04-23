#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0000"

#include <cassert>
#include <climits>

#include "integer/fused_operations.cpp"
#include "utility/macro/assert_eq.cpp"

#include "test/mini/qq.cpp"

int main() {
  assert_eq(fused_mul_add(65536, 32768, -1), 2147483647);
  assert_eq(fused_add_mod(1000, 1000, 900), 200);
  assert_eq(fused_add_mod(2000000000, 2000000000, 2100000000), 1900000000);
  assert_eq(fused_mul_mod(1000000, 1000000, 998244353), 757402647);

  assert_eq(fused_mul_mod(+1000000000, +1000000000, +1000000007), 49);
  assert_eq(fused_mul_mod(+1000000000, +1000000000, -1000000007), -999999958);
  assert_eq(fused_mul_mod(+1000000000, -1000000000, +1000000007), 999999958);
  assert_eq(fused_mul_mod(+1000000000, -1000000000, -1000000007), -49);
  assert_eq(fused_mul_mod(-1000000000, +1000000000, +1000000007), 999999958);
  assert_eq(fused_mul_mod(-1000000000, +1000000000, -1000000007), -49);
  assert_eq(fused_mul_mod(-1000000000, -1000000000, +1000000007), 49);
  assert_eq(fused_mul_mod(-1000000000, -1000000000, -1000000007), -999999958);

  assert_eq(fused_add_mod(2, 3, +5), 0);
  assert_eq(fused_add_mod(2, 3, -5), 0);

  assert_eq(fused_mul_mod(+3, +4, +2), 0);
  assert_eq(fused_mul_mod(+3, +4, -2), 0);
  assert_eq(fused_mul_mod(+3, -4, +2), 0);
  assert_eq(fused_mul_mod(+3, -4, -2), 0);
  assert_eq(fused_mul_mod(-3, +4, +2), 0);
  assert_eq(fused_mul_mod(-3, +4, -2), 0);
  assert_eq(fused_mul_mod(-3, -4, +2), 0);
  assert_eq(fused_mul_mod(-3, -4, -2), 0);

  assert_eq(fused_mul_mod(INT_MIN, -1, -1), 0);
  assert_eq(fused_mul_mod(INT_MIN, +1, -1), 0);
  assert_eq(fused_mul_mod(INT_MIN, -1, +1), 0);
  assert_eq(fused_mul_mod(INT_MIN, +1, +1), 0);

  assert_eq(fused_mul_min(1000000000, 1000000000, 2000000000), 2000000000);
  assert_eq(fused_mul_min(1000, 1000, 2000000000), 1000000);
  assert_eq(fused_mul_min(100, -100, 0), -10000);
  assert_eq(fused_mul_min(-100, -100, 0), 0);

  qq();  // dummy
}
