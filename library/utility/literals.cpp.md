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


# :heavy_check_mark: ユーザ定義リテラル <small>(utility/literals.cpp)</small>

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#67b732dc42aaffa9056d34cc477c863c">utility</a>
* <a href="{{ site.github.repository_url }}/blob/master/utility/literals.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-06 04:52:14+09:00




## Required by

* :heavy_check_mark: <a href="../DataStructure/bit_vector.cpp.html">rank/select 辞書 <small>(DataStructure/bit_vector.cpp)</small></a>
* :heavy_check_mark: <a href="../DataStructure/dynamic_bitvector.cpp.html">動的ビットベクトル <small>(DataStructure/dynamic_bitvector.cpp)</small></a>
* :heavy_check_mark: <a href="../DataStructure/wavelet_matrix.cpp.html">ウェーブレット行列 <small>(DataStructure/wavelet_matrix.cpp)</small></a>
* :heavy_check_mark: <a href="../Graph/dinitz.cpp.html">最大流 (Dinitz 法) <small>(Graph/dinitz.cpp)</small></a>
* :heavy_check_mark: <a href="../Graph/lowest_common_ancestor_segment_tree.cpp.html">最深共通祖先 (segment tree) <small>(Graph/lowest_common_ancestor_segment_tree.cpp)</small></a>
* :heavy_check_mark: <a href="../Graph/lowest_common_ancestor_sparse_table.cpp.html">最深共通祖先 (sparse table) <small>(Graph/lowest_common_ancestor_sparse_table.cpp)</small></a>
* :heavy_check_mark: <a href="../Graph/lowest_common_ancestor_squaring.cpp.html">最深共通祖先 (squaring) <small>(Graph/lowest_common_ancestor_squaring.cpp)</small></a>
* :heavy_check_mark: <a href="../Math/lp_solver.cpp.html">線形計画法ソルバ (simplex 法) <small>(Math/lp_solver.cpp)</small></a>
* :heavy_check_mark: <a href="../String/rolling_hash_l61m1.cpp.html">mod 2^61-1 のローリングハッシュ <small>(String/rolling_hash_l61m1.cpp)</small></a>
* :heavy_check_mark: <a href="../String/sa_is.cpp.html">接尾辞配列 + induced sort <small>(String/sa_is.cpp)</small></a>
* :heavy_check_mark: <a href="../String/suffix_array.cpp.html">接尾辞配列 <small>(String/suffix_array.cpp)</small></a>
* :heavy_check_mark: <a href="../String/tree_attack.cpp.html">ロリハを衝突させるやつ (tree attack) <small>(String/tree_attack.cpp)</small></a>
* :heavy_check_mark: <a href="../algorithm/moebius_transform.cpp.html">高速 Möbius 変換 <small>(algorithm/moebius_transform.cpp)</small></a>
* :warning: <a href="../integer/fused_multiply.cpp.html">乗算との複合演算 <small>(integer/fused_multiply.cpp)</small></a>
* :warning: <a href="../integer/mul_upper.cpp.html">整数の乗算の上位ワード <small>(integer/mul_upper.cpp)</small></a>
* :warning: <a href="../integer/overflow.cpp.html">オーバーフロー判定つき演算 <small>(integer/overflow.cpp)</small></a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/aoj_2178.test.cpp.html">test/aoj_2178.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj_2313.test.cpp.html">test/aoj_2313.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj_2446.test.cpp.html">test/aoj_2446.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj_2580.test.cpp.html">test/aoj_2580.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj_2911.test.cpp.html">test/aoj_2911.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj_2976.test.cpp.html">test/aoj_2976.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj_3110.test.cpp.html">test/aoj_3110.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj_3112.test.cpp.html">test/aoj_3112.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj_3112_sa_is.test.cpp.html">test/aoj_3112_sa_is.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj_ALDS1_14_B_l61m1.test.cpp.html">test/aoj_ALDS1_14_B_l61m1.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj_ALDS1_5_D.test.cpp.html">test/aoj_ALDS1_5_D.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj_DPL_1_D.test.cpp.html">test/aoj_DPL_1_D.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj_GRL_5_C_segment_tree.test.cpp.html">test/aoj_GRL_5_C_segment_tree.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj_GRL_5_C_sparse_table.test.cpp.html">test/aoj_GRL_5_C_sparse_table.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj_GRL_5_C_squaring.test.cpp.html">test/aoj_GRL_5_C_squaring.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yc_3014.test.cpp.html">test/yc_3014.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yc_878.test.cpp.html">test/yc_878.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yc_878_reversed.test.cpp.html">test/yc_878_reversed.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yj_lca_squaring.test.cpp.html">test/yj_lca_squaring.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yj_range_kth_smallest.test.cpp.html">test/yj_range_kth_smallest.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yj_suffixarray.test.cpp.html">test/yj_suffixarray.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#ifndef H_int_literals
#define H_int_literals

/**
 * @brief ユーザ定義リテラル
 * @author えびちゃん
 */

#include <cstddef>
#include <cstdint>

constexpr intmax_t  operator ""_jd(unsigned long long n) { return n; }
constexpr uintmax_t operator ""_ju(unsigned long long n) { return n; }
constexpr size_t    operator ""_zu(unsigned long long n) { return n; }
constexpr ptrdiff_t operator ""_td(unsigned long long n) { return n; }

#endif  /* !defined(H_int_literals) */

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "utility/literals.cpp"



/**
 * @brief ユーザ定義リテラル
 * @author えびちゃん
 */

#include <cstddef>
#include <cstdint>

constexpr intmax_t  operator ""_jd(unsigned long long n) { return n; }
constexpr uintmax_t operator ""_ju(unsigned long long n) { return n; }
constexpr size_t    operator ""_zu(unsigned long long n) { return n; }
constexpr ptrdiff_t operator ""_td(unsigned long long n) { return n; }



```
{% endraw %}

<a href="../../index.html">Back to top page</a>

