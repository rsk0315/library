#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0000"

#include <cassert>
#include <climits>
#include <limits>
#include <random>
#include <type_traits>

#include "utility/macro/assert_eq.cpp"
#include "integer/fused_operations.cpp"

#include "test/mini/qq.cpp"

  // test_mul_add();
  // test_mul_min();
  // test_add_mod();
  // test_mul_mod();

std::mt19937_64 rng;

template <typename Tp>
static constexpr Tp min_v = std::numeric_limits<Tp>::min();
template <typename Tp>
static constexpr Tp max_v = std::numeric_limits<Tp>::max();

template <typename Tp>
int test_add_mod(int rep) {
  using large_type = typename std::conditional<std::is_signed_v<Tp>, __int128, unsigned __int128>::type;
  std::uniform_int_distribution<Tp> u(min_v<Tp>, max_v<Tp>);
  int neg = 0, pos = 0;
  for (int i = 0; i < rep; ++i) {
    Tp x = u(rng);
    Tp y = u(rng);
    Tp z = u(rng);
    if (z == 0) continue;
    Tp w = (large_type(x) + large_type(y)) % large_type(z);
    if (w != 0 && ((w < 0) != (z < 0))) w += z;
    std::cerr << __PRETTY_FUNCTION__ << '\n';
    std::cerr << "fused_add_mod(" << x << ", " << y << ", " << z << "): " << w << '\n';
    assert_eq(fused_add_mod(x, y, z), w);
    ++((y < 0)? neg: pos);
  }
  assert(pos > 0 && (std::is_unsigned_v<Tp> || neg > 0));
  return neg + pos;
}

void test_add_mod() {
  fprintf(stderr, "%d tests passed.\n", test_add_mod<signed int>(10000));
  fprintf(stderr, "%d tests passed.\n", test_add_mod<unsigned int>(10000));
  fprintf(stderr, "%d tests passed.\n", test_add_mod<signed long>(10000));
  fprintf(stderr, "%d tests passed.\n", test_add_mod<unsigned long>(10000));
}

template <typename Tp>
int test_mul_mod(int rep) {
  using large_type = typename std::conditional<std::is_signed_v<Tp>, __int128, unsigned __int128>::type;
  std::uniform_int_distribution<Tp> u(min_v<Tp>, max_v<Tp>);
  int neg = 0, pos = 0;
  for (int i = 0; i < rep; ++i) {
    Tp x = u(rng);
    Tp y = u(rng);
    Tp z = u(rng);
    if (z == 0) continue;
    Tp w = (large_type(x) * large_type(y)) % large_type(z);
    if (w != 0 && ((w < 0) != (z < 0))) w += z;
    std::cerr << __PRETTY_FUNCTION__ << '\n';
    std::cerr << "fused_mul_mod(" << x << ", " << y << ", " << z << "): " << w << '\n';
    assert_eq(fused_mul_mod(x, y, z), w);
    ++((y < 0)? neg: pos);
  }
  assert(pos > 0 && (std::is_unsigned_v<Tp> || neg > 0));
  return neg + pos;
}

void test_mul_mod() {
  fprintf(stderr, "%d tests passed.\n", test_mul_mod<signed int>(10000));
  fprintf(stderr, "%d tests passed.\n", test_mul_mod<unsigned int>(10000));
  fprintf(stderr, "%d tests passed.\n", test_mul_mod<signed long>(10000));
  fprintf(stderr, "%d tests passed.\n", test_mul_mod<unsigned long>(10000));
}

int main() {
  assert_eq(fused_mul_add(65536, 32768, -1), 2147483647);
  assert_eq(fused_add_mod(1000, 1000, 900), 200);
  assert_eq(fused_add_mod(2000000000, 2000000000, 2100000000), 1900000000);
  assert_eq(fused_mul_mod(1000000, 1000000, 998244353), 757402647);

  assert_eq(fused_mul_add(65536u, 32768u, -1u), 2147483647u);
  assert_eq(fused_add_mod(1000u, 1000u, 900u), 200u);
  assert_eq(fused_add_mod(2000000000u, 2000000000u, 2100000000u), 1900000000u);
  assert_eq(fused_mul_mod(1000000u, 1000000u, 998244353u), 757402647u);

  assert_eq(fused_add_mod(1, 3, -3), -2);
  assert_eq(fused_add_mod(1, -3, 3), 1);

  assert_eq(fused_mul_mod(+1000000000, +1000000000, +1000000007), 49);
  assert_eq(fused_mul_mod(+1000000000, +1000000000, -1000000007), -999999958);
  assert_eq(fused_mul_mod(+1000000000, -1000000000, +1000000007), 999999958);
  assert_eq(fused_mul_mod(+1000000000, -1000000000, -1000000007), -49);
  assert_eq(fused_mul_mod(-1000000000, +1000000000, +1000000007), 999999958);
  assert_eq(fused_mul_mod(-1000000000, +1000000000, -1000000007), -49);
  assert_eq(fused_mul_mod(-1000000000, -1000000000, +1000000007), 49);
  assert_eq(fused_mul_mod(-1000000000, -1000000000, -1000000007), -999999958);

  assert_eq(fused_mul_mod(+1000000000u, +1000000000u, +1000000007u), 49u);
  assert_eq(fused_mul_mod(+1000000000u, +1000000000u, -1000000007u), 1609396939u);
  assert_eq(fused_mul_mod(+1000000000u, -1000000000u, +1000000007u), 935229096u);
  assert_eq(fused_mul_mod(+1000000000u, -1000000000u, -1000000007u), 410065422u);
  assert_eq(fused_mul_mod(-1000000000u, +1000000000u, +1000000007u), 935229096u);
  assert_eq(fused_mul_mod(-1000000000u, +1000000000u, -1000000007u), 410065422u);
  assert_eq(fused_mul_mod(-1000000000u, -1000000000u, +1000000007u), 711885781u);
  assert_eq(fused_mul_mod(-1000000000u, -1000000000u, -1000000007u), 49u);

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

  assert_eq(fused_mul_mod(1000000000000000000L, 1000000000000000000L, 2305843009213693951L),
            1824060670036424877L);

  test_add_mod();
  test_mul_mod();

  qq();  // dummy
}
