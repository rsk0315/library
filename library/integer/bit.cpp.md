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


# :heavy_check_mark: ビット演算 <small>(integer/bit.cpp)</small>

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#157db7df530023575515d366c9b672e8">integer</a>
* <a href="{{ site.github.repository_url }}/blob/master/integer/bit.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-24 20:58:06+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/test/aoj_1322.test.cpp.html">test/aoj_1322.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj_2446.test.cpp.html">test/aoj_2446.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj_DPL_1_D.test.cpp.html">test/aoj_DPL_1_D.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj_DPL_5_A.test.cpp.html">test/aoj_DPL_5_A.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj_DPL_5_C.test.cpp.html">test/aoj_DPL_5_C.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj_DPL_5_G.test.cpp.html">test/aoj_DPL_5_G.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj_DPL_5_I.test.cpp.html">test/aoj_DPL_5_I.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj_DSL_2_G.test.cpp.html">test/aoj_DSL_2_G.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj_DSL_2_H.test.cpp.html">test/aoj_DSL_2_H.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj_GRL_5_C_segment_tree.test.cpp.html">test/aoj_GRL_5_C_segment_tree.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj_GRL_5_C_sparse_table.test.cpp.html">test/aoj_GRL_5_C_sparse_table.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj_GRL_5_E.test.cpp.html">test/aoj_GRL_5_E.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yc_551.test.cpp.html">test/yc_551.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yj_convolution_mod.test.cpp.html">test/yj_convolution_mod.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yj_convolution_mod_1000000007.test.cpp.html">test/yj_convolution_mod_1000000007.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yj_inv_of_formal_power_series.test.cpp.html">test/yj_inv_of_formal_power_series.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yj_log_of_formal_power_series.test.cpp.html">test/yj_log_of_formal_power_series.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yj_multipoint_evaluation.test.cpp.html">test/yj_multipoint_evaluation.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yj_polynomial_interpolation.test.cpp.html">test/yj_polynomial_interpolation.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yj_range_affine_range_sum.test.cpp.html">test/yj_range_affine_range_sum.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
/** 
 * @brief ビット演算
 * @author えびちゃん
 */

#ifndef H_bit
#define H_bit

#include <climits>
#include <type_traits>

// #ifdef __has_builtin
int clz(unsigned n) { return __builtin_clz(n); }
int clz(unsigned long n) { return __builtin_clzl(n); }
int clz(unsigned long long n) { return __builtin_clzll(n); }
int ctz(unsigned n) { return __builtin_ctz(n); }
int ctz(unsigned long n) { return __builtin_ctzl(n); }
int ctz(unsigned long long n) { return __builtin_ctzll(n); }
int popcount(unsigned n) { return __builtin_popcount(n); }
int popcount(unsigned long n) { return __builtin_popcountl(n); }
int popcount(unsigned long long n) { return __builtin_popcountll(n); }
// #else
// TODO: implement
// #endif

template <typename Tp>
auto clz(Tp n) -> typename std::enable_if<std::is_signed<Tp>::value, int>::type {
  return clz(static_cast<typename std::make_unsigned<Tp>::type>(n));
}
template <typename Tp>
auto ctz(Tp n) -> typename std::enable_if<std::is_signed<Tp>::value, int>::type {
  return ctz(static_cast<typename std::make_unsigned<Tp>::type>(n));
}
template <typename Tp>
auto popcount(Tp n) -> typename std::enable_if<std::is_signed<Tp>::value, int>::type {
  return popcount(static_cast<typename std::make_unsigned<Tp>::type>(n));
}

template <typename Tp>
int parity(Tp n) { return popcount(n) & 1; }
template <typename Tp>
int ilog2(Tp n) {
  return (CHAR_BIT * sizeof(Tp) - 1) - clz(static_cast<typename std::make_unsigned<Tp>::type>(n));
}
template <typename Tp>
Tp ceil2(Tp n) {
  if (!(n & (n-1))) return n;
  return Tp(2) << ilog2(n);
}
template <typename Tp>
Tp reverse(Tp n) {
  static constexpr Tp b1 = static_cast<Tp>(0x5555555555555555);
  static constexpr Tp b2 = static_cast<Tp>(0x3333333333333333);
  static constexpr Tp b4 = static_cast<Tp>(0x0F0F0F0F0F0F0F0F);
  static constexpr Tp b8 = static_cast<Tp>(0x00FF00FF00FF00FF);
  static constexpr Tp bx = static_cast<Tp>(0x0000FFFF0000FFFF);
  n = ((n & b1) << 1) | ((n >> 1) & b1);
  n = ((n & b2) << 2) | ((n >> 2) & b2);
  n = ((n & b4) << 4) | ((n >> 4) & b4);
  n = ((n & b8) << 8) | ((n >> 8) & b8);
  n = ((n & bx) << 16) | ((n >> 16) & bx);
  if ((sizeof n) > 4) n = (n << 32) | (n >> 32);
  return n;
}

#endif  /* !defined(H_bit) */

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "integer/bit.cpp"
/** 
 * @brief ビット演算
 * @author えびちゃん
 */

#ifndef H_bit
#define H_bit

#include <climits>
#include <type_traits>

// #ifdef __has_builtin
int clz(unsigned n) { return __builtin_clz(n); }
int clz(unsigned long n) { return __builtin_clzl(n); }
int clz(unsigned long long n) { return __builtin_clzll(n); }
int ctz(unsigned n) { return __builtin_ctz(n); }
int ctz(unsigned long n) { return __builtin_ctzl(n); }
int ctz(unsigned long long n) { return __builtin_ctzll(n); }
int popcount(unsigned n) { return __builtin_popcount(n); }
int popcount(unsigned long n) { return __builtin_popcountl(n); }
int popcount(unsigned long long n) { return __builtin_popcountll(n); }
// #else
// TODO: implement
// #endif

template <typename Tp>
auto clz(Tp n) -> typename std::enable_if<std::is_signed<Tp>::value, int>::type {
  return clz(static_cast<typename std::make_unsigned<Tp>::type>(n));
}
template <typename Tp>
auto ctz(Tp n) -> typename std::enable_if<std::is_signed<Tp>::value, int>::type {
  return ctz(static_cast<typename std::make_unsigned<Tp>::type>(n));
}
template <typename Tp>
auto popcount(Tp n) -> typename std::enable_if<std::is_signed<Tp>::value, int>::type {
  return popcount(static_cast<typename std::make_unsigned<Tp>::type>(n));
}

template <typename Tp>
int parity(Tp n) { return popcount(n) & 1; }
template <typename Tp>
int ilog2(Tp n) {
  return (CHAR_BIT * sizeof(Tp) - 1) - clz(static_cast<typename std::make_unsigned<Tp>::type>(n));
}
template <typename Tp>
Tp ceil2(Tp n) {
  if (!(n & (n-1))) return n;
  return Tp(2) << ilog2(n);
}
template <typename Tp>
Tp reverse(Tp n) {
  static constexpr Tp b1 = static_cast<Tp>(0x5555555555555555);
  static constexpr Tp b2 = static_cast<Tp>(0x3333333333333333);
  static constexpr Tp b4 = static_cast<Tp>(0x0F0F0F0F0F0F0F0F);
  static constexpr Tp b8 = static_cast<Tp>(0x00FF00FF00FF00FF);
  static constexpr Tp bx = static_cast<Tp>(0x0000FFFF0000FFFF);
  n = ((n & b1) << 1) | ((n >> 1) & b1);
  n = ((n & b2) << 2) | ((n >> 2) & b2);
  n = ((n & b4) << 4) | ((n >> 4) & b4);
  n = ((n & b8) << 8) | ((n >> 8) & b8);
  n = ((n & bx) << 16) | ((n >> 16) & bx);
  if ((sizeof n) > 4) n = (n << 32) | (n >> 32);
  return n;
}

#endif  /* !defined(H_bit) */

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

