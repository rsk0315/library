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


# :heavy_check_mark: 型依存の定数 <small>(utility/limits.cpp)</small>

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#67b732dc42aaffa9056d34cc477c863c">utility</a>
* <a href="{{ site.github.repository_url }}/blob/master/utility/limits.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-06 23:03:06+09:00




## Required by

* :heavy_check_mark: <a href="../DataStructure/li_chao_tree.cpp.html">Li-Chao tree <small>(DataStructure/li_chao_tree.cpp)</small></a>
* :heavy_check_mark: <a href="../Graph/dinitz.cpp.html">最大流 (Dinitz 法) <small>(Graph/dinitz.cpp)</small></a>
* :warning: <a href="../Graph/pre17/shortest_path.cpp.html">グラフ上の最短距離 <small>(Graph/pre17/shortest_path.cpp)</small></a>
* :warning: <a href="../Graph/shortest_path.cpp.html">グラフ上の最短距離 <small>(Graph/shortest_path.cpp)</small></a>
* :heavy_check_mark: <a href="../Math/lp_solver.cpp.html">線形計画法ソルバ (simplex 法) <small>(Math/lp_solver.cpp)</small></a>
* :heavy_check_mark: <a href="../algorithm/online_to_offline_optimization.cpp.html">オンライン・オフライン変換 <small>(algorithm/online_to_offline_optimization.cpp)</small></a>
* :warning: <a href="action/add_max.cpp.html">区間最大値・区間加算用のヘルパークラス <small>(utility/action/add_max.cpp)</small></a>
* :heavy_check_mark: <a href="action/add_min.cpp.html">区間最小値・区間加算用のヘルパークラス <small>(utility/action/add_min.cpp)</small></a>
* :warning: <a href="action/min_min.cpp.html">区間最小値・区間最小値更新用のヘルパークラス <small>(utility/action/min_min.cpp)</small></a>
* :heavy_check_mark: <a href="monoid/max.cpp.html">max を得る演算のモノイド <small>(utility/monoid/max.cpp)</small></a>
* :heavy_check_mark: <a href="monoid/min.cpp.html">min を得る演算のモノイド <small>(utility/monoid/min.cpp)</small></a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/aoj_0575.test.cpp.html">test/aoj_0575.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj_0613.test.cpp.html">test/aoj_0613.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj_1595.test.cpp.html">test/aoj_1595.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj_2313.test.cpp.html">test/aoj_2313.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj_2911.test.cpp.html">test/aoj_2911.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj_2976.test.cpp.html">test/aoj_2976.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj_DSL_2_A.test.cpp.html">test/aoj_DSL_2_A.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj_DSL_2_H.test.cpp.html">test/aoj_DSL_2_H.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj_DSL_3_D.test.cpp.html">test/aoj_DSL_3_D.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yc_703_onoff.test.cpp.html">test/yc_703_onoff.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yc_704_onoff.test.cpp.html">test/yc_704_onoff.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yc_705_onoff.test.cpp.html">test/yc_705_onoff.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yc_878.test.cpp.html">test/yc_878.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yc_878_reversed.test.cpp.html">test/yc_878_reversed.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yj_bipartitematching.test.cpp.html">test/yj_bipartitematching.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yj_line_add_get_min_li_chao_tree.test.cpp.html">test/yj_line_add_get_min_li_chao_tree.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yj_segment_add_get_min.test.cpp.html">test/yj_segment_add_get_min.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yj_staticrmq.test.cpp.html">test/yj_staticrmq.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#ifndef H_limits
#define H_limits

/**
 * @brief 型依存の定数
 * @author えびちゃん
 */

#include <limits>

template <typename Tp>
class limits: public std::numeric_limits<Tp> {};

#endif  /* !defined(H_limits) */

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "utility/limits.cpp"



/**
 * @brief 型依存の定数
 * @author えびちゃん
 */

#include <limits>

template <typename Tp>
class limits: public std::numeric_limits<Tp> {};



```
{% endraw %}

<a href="../../index.html">Back to top page</a>

