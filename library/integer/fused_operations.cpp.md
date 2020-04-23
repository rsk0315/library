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
<script type="text/javascript" src="../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../assets/css/copy-button.css" />


# :heavy_check_mark: 乗算との複合演算 <small>(integer/fused_operations.cpp)</small>

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#157db7df530023575515d366c9b672e8">integer</a>
* <a href="{{ site.github.repository_url }}/blob/master/integer/fused_operations.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-23 22:32:03+09:00




## Depends on

* :heavy_check_mark: <a href="mul_upper.cpp.html">整数の乗算の上位ワード <small>(integer/mul_upper.cpp)</small></a>
* :heavy_check_mark: <a href="overflow.cpp.html">オーバーフロー判定つき演算 <small>(integer/overflow.cpp)</small></a>
* :heavy_check_mark: <a href="../utility/literals.cpp.html">ユーザ定義リテラル <small>(utility/literals.cpp)</small></a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/mini/fused_operations.test.cpp.html">test/mini/fused_operations.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#ifndef H_fused_operations
#define H_fused_operations

/**
 * @brief 乗算との複合演算
 * @author えびちゃん
 */

#include <climits>
#include <algorithm>
#include <type_traits>

#include "integer/overflow.cpp"
#include "integer/mul_upper.cpp"

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
  if ((x %= z) != 0 && ((x < 0) != (z < 0))) x += z;
  if ((y %= z) != 0 && ((y < 0) != (z < 0))) y += z;
  x -= z - y;
  if ((x %= z) != 0 && ((x < 0) != (z < 0))) x += z;
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

#endif  /* !defined(H_fused_operations) */

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "integer/fused_operations.cpp"



/**
 * @brief 乗算との複合演算
 * @author えびちゃん
 */

#include <climits>
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
  if ((x %= z) != 0 && ((x < 0) != (z < 0))) x += z;
  if ((y %= z) != 0 && ((y < 0) != (z < 0))) y += z;
  x -= z - y;
  if ((x %= z) != 0 && ((x < 0) != (z < 0))) x += z;
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



```
{% endraw %}

<a href="../../index.html">Back to top page</a>

