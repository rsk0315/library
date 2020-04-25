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


# :question: ビット演算 <small>(integer/bit.cpp)</small>

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#157db7df530023575515d366c9b672e8">integer</a>
* <a href="{{ site.github.repository_url }}/blob/master/integer/bit.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-10 05:36:19+09:00




## Required by

* :heavy_check_mark: <a href="../DataStructure/disjoint_sparse_table.cpp.html">disjoint sparse table <small>(DataStructure/disjoint_sparse_table.cpp)</small></a>
* :heavy_check_mark: <a href="../DataStructure/dynamic_bitvector.cpp.html">動的ビットベクトル <small>(DataStructure/dynamic_bitvector.cpp)</small></a>
* :heavy_check_mark: <a href="../DataStructure/segment_tree.cpp.html">区間作用・区間和セグメント木 <small>(DataStructure/segment_tree.cpp)</small></a>
* :heavy_check_mark: <a href="../DataStructure/sparse_table.cpp.html">sparse table <small>(DataStructure/sparse_table.cpp)</small></a>
* :x: <a href="../Graph/lowest_common_ancestor_segment_tree.cpp.html">最深共通祖先 (segment tree) <small>(Graph/lowest_common_ancestor_segment_tree.cpp)</small></a>
* :x: <a href="../Graph/lowest_common_ancestor_sparse_table.cpp.html">最深共通祖先 (sparse table) <small>(Graph/lowest_common_ancestor_sparse_table.cpp)</small></a>
* :heavy_check_mark: <a href="../ModularArithmetic/factorial.cpp.html">階乗の高速計算 <small>(ModularArithmetic/factorial.cpp)</small></a>
* :heavy_check_mark: <a href="../ModularArithmetic/interpolation.cpp.html">補間多項式 <small>(ModularArithmetic/interpolation.cpp)</small></a>
* :heavy_check_mark: <a href="../ModularArithmetic/operations.cpp.html">合同算術の基本演算 <small>(ModularArithmetic/operations.cpp)</small></a>
* :heavy_check_mark: <a href="../ModularArithmetic/polynomial.cpp.html">多項式 <small>(ModularArithmetic/polynomial.cpp)</small></a>
* :heavy_check_mark: <a href="../algorithm/moebius_transform.cpp.html">高速 Möbius 変換 <small>(algorithm/moebius_transform.cpp)</small></a>


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
* :x: <a href="../../verify/test/aoj_GRL_5_C_segment_tree.test.cpp.html">test/aoj_GRL_5_C_segment_tree.test.cpp</a>
* :x: <a href="../../verify/test/aoj_GRL_5_C_sparse_table.test.cpp.html">test/aoj_GRL_5_C_sparse_table.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj_GRL_5_E.test.cpp.html">test/aoj_GRL_5_E.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yc_1036_disjoint_sparse_table.test.cpp.html">test/yc_1036_disjoint_sparse_table.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yc_1036_sparse_table.test.cpp.html">test/yc_1036_sparse_table.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yc_502.test.cpp.html">test/yc_502.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yc_551.test.cpp.html">test/yc_551.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yj_convolution_mod.test.cpp.html">test/yj_convolution_mod.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yj_convolution_mod_1000000007.test.cpp.html">test/yj_convolution_mod_1000000007.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yj_convolution_mod_raw.test.cpp.html">test/yj_convolution_mod_raw.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yj_inv_of_formal_power_series.test.cpp.html">test/yj_inv_of_formal_power_series.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yj_log_of_formal_power_series.test.cpp.html">test/yj_log_of_formal_power_series.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yj_multipoint_evaluation.test.cpp.html">test/yj_multipoint_evaluation.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yj_polynomial_interpolation.test.cpp.html">test/yj_polynomial_interpolation.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yj_range_affine_range_sum.test.cpp.html">test/yj_range_affine_range_sum.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#ifndef H_bit
#define H_bit

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



```
{% endraw %}

<a href="../../index.html">Back to top page</a>

