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


# :question: 合同算術の基本演算 <small>(ModularArithmetic/operations.cpp)</small>

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#495e431c85de4c533fce4ff12db613fe">ModularArithmetic</a>
* <a href="{{ site.github.repository_url }}/blob/master/ModularArithmetic/operations.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-10 05:36:19+09:00




## Depends on

* :question: <a href="../integer/bit.cpp.html">ビット演算 <small>(integer/bit.cpp)</small></a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/aoj_1322.test.cpp.html">test/aoj_1322.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj_DPL_5_A.test.cpp.html">test/aoj_DPL_5_A.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj_DPL_5_C.test.cpp.html">test/aoj_DPL_5_C.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj_DPL_5_G.test.cpp.html">test/aoj_DPL_5_G.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj_DPL_5_I.test.cpp.html">test/aoj_DPL_5_I.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yc_551.test.cpp.html">test/yc_551.test.cpp</a>
* :x: <a href="../../verify/test/yj_log_of_formal_power_series.test.cpp.html">test/yj_log_of_formal_power_series.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#ifndef H_mod_operations
#define H_mod_operations

/**
 * @brief 合同算術の基本演算
 * @author えびちゃん
 */

#include <stdexcept>
#include <vector>

#include "integer/bit.cpp"

template <typename ModInt>
ModInt pow(ModInt const& n, intmax_t iexp) {
  ModInt res(1);
  for (ModInt dbl = n; iexp; iexp >>= 1) {
    if (iexp & 1) res *= dbl;
    dbl *= dbl;
  }
  return res;
}

template <typename ModInt>
ModInt sqrt(ModInt const& n) {
  if (n == 0) return n;

  using value_type = typename ModInt::value_type;

  intmax_t const p = n.get_modulo();
  if (p % 4 == 3) {
    ModInt r = pow(n, (p+1) / 4);
    if (r * r == n) return r;
    throw std::logic_error("quadratic nonresidue");
  }

  value_type s = ctz(p-1);
  value_type q = (p-1) >> s;

  ModInt z;
  for (value_type z0 = 2; z0 < p; ++z0) {
    z = ModInt(z0);
    if (pow(z, (p-1) / 2) == -1) break;
  }

  value_type m = s;
  ModInt c = pow(z, q);
  ModInt t = pow(n, q);
  ModInt r = pow(n, (q+1) / 2);

  while (true) {
    if (t == 0) return 0;
    if (t == 1) return r;

    value_type i = 0;
    for (auto tt = t; tt != 1; ++i) tt *= tt;
    if (i == m) throw std::logic_error("quadratic nonresidue");
    auto b = c;
    for (value_type j = 0; j < m-i-1; ++j) b *= b;
    m = i;
    c = b * b;
    t *= c;
    r *= b;
  }
}

template <typename ModInt>
std::vector<ModInt> sqrt_all(ModInt const& n) {
  try {
    auto r = sqrt(n);
    if (r == -r) return {r};
    return {r, -r};
  } catch (std::logic_error const&) {
    return {};
  }
}

template <typename ModPolynomial>
ModPolynomial log(ModPolynomial const& f) {
  auto g = f;
  g.differentiate();
  g *= f.inverse(f.degree()+1);
  g.integrate();
  return g;
}

#endif  /* !defined(H_mod_operations) */

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "ModularArithmetic/operations.cpp"



/**
 * @brief 合同算術の基本演算
 * @author えびちゃん
 */

#include <stdexcept>
#include <vector>

#line 1 "integer/bit.cpp"



/** 
 * @brief ビット演算
 * @author えびちゃん
 */

// XXX integral promotion 関連の注意をあまりしていません

#include <climits>
#include <type_traits>

template <typename Tp>
constexpr auto countl_zero(Tp n)
  -> typename std::enable_if<std::is_unsigned<Tp>::value, int>::type
{
  using value_type = typename std::make_unsigned<Tp>::type;
  int bits = (sizeof(value_type) * CHAR_BIT);
  if (n == 0) return bits;
  int res = 0;
  for (int i = bits / 2; i > 0; i /= 2) {
    value_type mask = ((static_cast<value_type>(1) << i) - 1) << i;
    if (n & mask) n >>= i;
    else res += i;
  }
  return res;
}
template <typename Tp>
constexpr auto countl_one(Tp n)
  -> typename std::enable_if<std::is_unsigned<Tp>::value, int>::type
{
  using value_type = typename std::make_unsigned<Tp>::type;
  return countl_zero(static_cast<value_type>(~n));
}

template <typename Tp>
constexpr auto countr_zero(Tp n)
  -> typename std::enable_if<std::is_unsigned<Tp>::value, int>::type
{
  using value_type = typename std::make_unsigned<Tp>::type;
  int bits = (sizeof(value_type) * CHAR_BIT);
  if (n == 0) return bits;
  int res = 0;
  for (int i = bits / 2; i > 0; i /= 2) {
    value_type mask = ((static_cast<value_type>(1) << i) - 1);
    if (!(n & mask)) res += i, n >>= i;
  }
  return res;
}
template <typename Tp>
constexpr auto countr_one(Tp n)
  -> typename std::enable_if<std::is_unsigned<Tp>::value, int>::type
{
  using value_type = typename std::make_unsigned<Tp>::type;
  return countr_zero(static_cast<value_type>(~n));
}

constexpr unsigned long long half_mask[] = {
  0x5555555555555555uLL, 0x3333333333333333uLL, 0x0F0F0F0F0F0F0F0FuLL,
  0x00FF00FF00FF00FFuLL, 0x0000FFFF0000FFFFuLL, 0x00000000FFFFFFFFuLL
};

template <typename Tp>
constexpr auto popcount(Tp n)
  -> typename std::enable_if<std::is_unsigned<Tp>::value, int>::type
{
  int bits = static_cast<int>((sizeof n) * CHAR_BIT);
  for (int i = 0, j = 1; j < bits; ++i, j *= 2) {
    if (j <= 8) n = (n & half_mask[i]) + ((n >> j) & half_mask[i]);
    else n += n >> j;
  }
  return n & 0xFF;
}

template <typename Tp>
constexpr auto parity(Tp n)
  -> typename std::enable_if<std::is_unsigned<Tp>::value, int>::type
{ return popcount(n) & 1; }


template <typename Tp>
int clz(Tp n) { return countl_zero(static_cast<typename std::make_unsigned<Tp>::type>(n)); }
template <typename Tp>
int ctz(Tp n) { return countr_zero(static_cast<typename std::make_unsigned<Tp>::type>(n)); }

template <typename Tp>
int ilog2(Tp n) {
  return (CHAR_BIT * sizeof(Tp) - 1) - clz(static_cast<typename std::make_unsigned<Tp>::type>(n));
}
template <typename Tp>
bool is_pow2(Tp n) { return (n > 0) && ((n & (n-1)) == 0); }
template <typename Tp>
Tp floor2(Tp n) { return is_pow2(n)? n: static_cast<Tp>(1) << ilog2(n); }
template <typename Tp>
Tp ceil2(Tp n) { return is_pow2(n)? n: static_cast<Tp>(2) << ilog2(n); }

template <typename Tp>
constexpr auto reverse(Tp n)
  -> typename std::enable_if<std::is_unsigned<Tp>::value, Tp>::type
{
  int bits = static_cast<int>((sizeof n) * CHAR_BIT);
  for (int i = 0, j = 1; j < bits; ++i, j *= 2) {
    n = ((n & half_mask[i]) << j) | ((n >> j) & half_mask[i]);
  }
  return n;
}


#line 13 "ModularArithmetic/operations.cpp"

template <typename ModInt>
ModInt pow(ModInt const& n, intmax_t iexp) {
  ModInt res(1);
  for (ModInt dbl = n; iexp; iexp >>= 1) {
    if (iexp & 1) res *= dbl;
    dbl *= dbl;
  }
  return res;
}

template <typename ModInt>
ModInt sqrt(ModInt const& n) {
  if (n == 0) return n;

  using value_type = typename ModInt::value_type;

  intmax_t const p = n.get_modulo();
  if (p % 4 == 3) {
    ModInt r = pow(n, (p+1) / 4);
    if (r * r == n) return r;
    throw std::logic_error("quadratic nonresidue");
  }

  value_type s = ctz(p-1);
  value_type q = (p-1) >> s;

  ModInt z;
  for (value_type z0 = 2; z0 < p; ++z0) {
    z = ModInt(z0);
    if (pow(z, (p-1) / 2) == -1) break;
  }

  value_type m = s;
  ModInt c = pow(z, q);
  ModInt t = pow(n, q);
  ModInt r = pow(n, (q+1) / 2);

  while (true) {
    if (t == 0) return 0;
    if (t == 1) return r;

    value_type i = 0;
    for (auto tt = t; tt != 1; ++i) tt *= tt;
    if (i == m) throw std::logic_error("quadratic nonresidue");
    auto b = c;
    for (value_type j = 0; j < m-i-1; ++j) b *= b;
    m = i;
    c = b * b;
    t *= c;
    r *= b;
  }
}

template <typename ModInt>
std::vector<ModInt> sqrt_all(ModInt const& n) {
  try {
    auto r = sqrt(n);
    if (r == -r) return {r};
    return {r, -r};
  } catch (std::logic_error const&) {
    return {};
  }
}

template <typename ModPolynomial>
ModPolynomial log(ModPolynomial const& f) {
  auto g = f;
  g.differentiate();
  g *= f.inverse(f.degree()+1);
  g.integrate();
  return g;
}



```
{% endraw %}

<a href="../../index.html">Back to top page</a>

