---
layout: default
---

<!-- mathjax config similar to math.stackexchange -->
<script type="text/javascript" async
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js?config=TeX-MML-AM_CHTML">
</script>
<script type="text/x-mathjax-config">
  MathJax.Hub.Config({
    TeX: { equationNumbers: { autoNumber: "AMS" }},
    tex2jax: {
      inlineMath: [ ['$','$'] ],
      processEscapes: true
    },
    "HTML-CSS": { matchFontHeight: false },
    displayAlign: "left",
    displayIndent: "2em"
  });
</script>

<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/jquery-balloon-js@1.1.2/jquery.balloon.min.js" integrity="sha256-ZEYs9VrgAeNuPvs15E39OsyOJaIkXEEt10fzxJ20+2I=" crossorigin="anonymous"></script>
<script type="text/javascript" src="../../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../../assets/css/copy-button.css" />


# :heavy_check_mark: test/mini/fused_operations.test.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#9a6d2aa7b36e38045ca314a0baa2d4bd">test/mini</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/mini/fused_operations.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-07-11 14:53:01+09:00


* see: <a href="http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0000">http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0000</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/integer/fused_operations.cpp.html">乗算との複合演算 <small>(integer/fused_operations.cpp)</small></a>
* :heavy_check_mark: <a href="../../../library/integer/mul_upper.cpp.html">整数の乗算の上位ワード <small>(integer/mul_upper.cpp)</small></a>
* :heavy_check_mark: <a href="../../../library/integer/overflow.cpp.html">オーバーフロー判定つき演算 <small>(integer/overflow.cpp)</small></a>
* :heavy_check_mark: <a href="../../../library/utility/literals.cpp.html">ユーザ定義リテラル <small>(utility/literals.cpp)</small></a>
* :heavy_check_mark: <a href="../../../library/utility/macro/assert_eq.cpp.html">等値判定のテスト用マクロ <small>(utility/macro/assert_eq.cpp)</small></a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
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

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/mini/fused_operations.test.cpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0000"

#include <cassert>
#include <climits>
#include <limits>
#include <random>
#include <type_traits>

#line 1 "utility/macro/assert_eq.cpp"



/**
 * @brief 等値判定のテスト用マクロ
 * @author えびちゃん
 */

#line 10 "utility/macro/assert_eq.cpp"
#include <iomanip>
#include <iostream>

#define assert_eq(expr, expected_) do {                                 \
    auto found = (expr);                                                \
    auto expected = (expected_);                                        \
    std::cerr << std::setw(64) << std::setfill('-') << "\n";            \
    std::cerr << "expr:     " << #expr << '\n';                         \
    std::cerr << "expected: " << expected << '\n';                      \
    std::cerr << "found:    ";                                          \
    std::cerr << ((found != expected)? "\x1b[1;91m": "\x1b[1;92m");     \
    std::cerr << found << "\x1b[m" << '\n';                             \
    std::cerr << std::setw(64) << std::setfill('-') << "\n";            \
    assert(found == expected);                                          \
  } while (false)


#line 1 "integer/fused_operations.cpp"



/**
 * @brief 乗算との複合演算
 * @author えびちゃん
 */

#line 10 "integer/fused_operations.cpp"
#include <algorithm>
#include <type_traits>

#line 1 "integer/overflow.cpp"



/**
 * @brief オーバーフロー判定つき演算
 * @author えびちゃん
 */

#line 10 "integer/overflow.cpp"
#include <type_traits>

#line 1 "integer/mul_upper.cpp"



/**
 * @brief 整数の乗算の上位ワード
 * @author えびちゃん
 */

#include <cstdint>
#line 11 "integer/mul_upper.cpp"
#include <type_traits>
#include <utility>

#line 1 "utility/literals.cpp"



/**
 * @brief ユーザ定義リテラル
 * @author えびちゃん
 */

#include <cstddef>
#line 11 "utility/literals.cpp"

constexpr intmax_t  operator ""_jd(unsigned long long n) { return n; }
constexpr uintmax_t operator ""_ju(unsigned long long n) { return n; }
constexpr size_t    operator ""_zu(unsigned long long n) { return n; }
constexpr ptrdiff_t operator ""_td(unsigned long long n) { return n; }

constexpr int8_t   operator ""_i8(unsigned long long n)  { return n; }
constexpr int16_t  operator ""_i16(unsigned long long n) { return n; }
constexpr int32_t  operator ""_i32(unsigned long long n) { return n; }
constexpr int64_t  operator ""_i64(unsigned long long n) { return n; }
constexpr uint8_t  operator ""_u8(unsigned long long n)  { return n; }
constexpr uint16_t operator ""_u16(unsigned long long n) { return n; }
constexpr uint32_t operator ""_u32(unsigned long long n) { return n; }
constexpr uint64_t operator ""_u64(unsigned long long n) { return n; }


#line 15 "integer/mul_upper.cpp"

template <typename Tp>
auto mul_upper(Tp u, Tp v)
  -> typename std::enable_if<std::is_integral_v<Tp>, Tp>::type
{
  using value_type = Tp;
  using unsigned_type = typename std::make_unsigned<Tp>::type;
  unsigned_type hi;
  int const bits = CHAR_BIT * sizeof(value_type);
  if (false && (sizeof u) < sizeof(uintmax_t)) {
    uintmax_t mul = uintmax_t(u) * v;
    hi = mul >> bits;
    // XXX unsigned only
  } else {
    int const half_bits = bits / 2;
    unsigned_type const half_mask = (unsigned_type(1) << half_bits) - 1;
    unsigned_type u0 = u & half_mask, v0 = v & half_mask;
    unsigned_type u1 = unsigned_type(u) >> half_bits, v1 = unsigned_type(v) >> half_bits;
    unsigned_type w0 = u0 * v0;
    unsigned_type t = u1 * v0 + (w0 >> half_bits);
    unsigned_type w1 = t & half_mask;
    unsigned_type w2 = t >> half_bits;
    w1 += u0 * v1;
    hi = u1 * v1 + w2 + (w1 >> half_bits);
    if (u < 0) hi -= v;
    if (v < 0) hi -= u;
  }
  return hi;
}


#line 13 "integer/overflow.cpp"

template <typename Tp>
auto add_overflow(Tp x, Tp y, Tp& z)
  -> typename std::enable_if<std::is_integral_v<Tp>, bool>::type
{
  using unsigned_type = typename std::make_unsigned<Tp>::type;
  unsigned_type ux = x, uy = y;
  unsigned_type sign_bit = unsigned_type{1} << ((CHAR_BIT * sizeof(Tp)) - 1);
  if ((ux & sign_bit) ^ (uy & sign_bit)) return (z = x + y), false;
  if (((ux + uy) & sign_bit) != (ux & sign_bit)) return true;
  z = x + y;
  return false;
}

template <typename Tp>
auto sub_overflow(Tp x, Tp y, Tp& z)
  -> typename std::enable_if<std::is_integral_v<Tp>, bool>::type
{
  using unsigned_type = typename std::make_unsigned<Tp>::type;
  if (y == 0) return (z = x), false;
  unsigned_type uy = y;
  if (~(uy | (uy-1)) == 0 && y < 0) return true;
  return add_overflow(x, -y, z);
}

template <typename Tp>
auto mul_overflow(Tp x, Tp y, Tp& z)
  -> typename std::enable_if<std::is_integral_v<Tp>, bool>::type
{
  using unsigned_type = typename std::make_unsigned<Tp>::type;
  unsigned_type ux = x, uy = y;
  unsigned_type sign_bit = ~(~unsigned_type(0) >> 1);
  if (((ux * uy) & sign_bit) != ((ux & sign_bit) ^ (uy & sign_bit))) return true;
  z = x * y;
  return false;
}


#line 15 "integer/fused_operations.cpp"

template <typename Tp>
Tp fused_mul_add(Tp x, Tp y, Tp z) {
  // Return x * y + z without overflow
  using unsigned_type = typename std::make_unsigned<Tp>::type;
  unsigned_type ux = x, uy = y;
  unsigned_type lo = ux * uy;
  return lo + z;
}

template <typename Tp>
Tp fused_mul_min(Tp x, Tp y, Tp z) {
  // min(x * y, z) without overflow
  Tp w;
  if (mul_overflow(x, y, w)) return z;  // undefined if x*y < minimum
  return std::min(w, z);
}

template <typename Tp>
Tp fused_add_mod(Tp x, Tp y, Tp z) {
  // (x + y) % z, same sign as z, without overflow
  if (std::is_signed_v<Tp>) {
    if ((x %= z) != 0 && ((x < 0) != (z < 0))) x += z;
    if ((y %= z) != 0 && ((y < 0) != (z < 0))) y += z;
    x -= z - y;
    if ((x %= z) != 0 && ((x < 0) != (z < 0))) x += z;
  } else {
    x %= z;
    y %= z;
    x += ((x < z-y)? y: y-z);
  }
  return x;
}

template <typename Tp>
Tp fused_mul_mod(Tp x, Tp y, Tp z) {
  // (x * y) % z, same sign as z, without overflow
  using value_type = Tp;
  using unsigned_type = typename std::make_unsigned<Tp>::type;
  unsigned_type ux = x, uy = y;
  value_type hi = mul_upper(x, y) % z;
  int const bits = CHAR_BIT * sizeof(Tp);
  for (int i = 0; i < bits; ++i) {
    hi = fused_add_mod(hi, hi, z);
  }
  unsigned_type uxy = ux * uy;
  value_type loh = uxy >> (bits/2);
  value_type lol = uxy & (~unsigned_type(0) >> (bits/2));
  for (int i = 0; i < bits/2; ++i) {
    loh = fused_add_mod(loh, loh, z);
  }
  lol = fused_add_mod(loh, lol, z);
  return fused_add_mod(hi, lol, z);
}


#line 11 "test/mini/fused_operations.test.cpp"

#line 1 "test/mini/qq.cpp"



// @ignore

#include <cstdio>

void qq() {
  for (int i = 1; i <= 9; ++i)
    for (int j = 1; j <= 9; ++j)
      printf("%dx%d=%d\n", i, j, i*j);
}


#line 13 "test/mini/fused_operations.test.cpp"

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

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

