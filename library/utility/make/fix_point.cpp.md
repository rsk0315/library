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


# :question: ラムダ式の再帰 <small>(utility/make/fix_point.cpp)</small>

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#eea2354d8759bbd52e8bbb508d91fa66">utility/make</a>
* <a href="{{ site.github.repository_url }}/blob/master/utility/make/fix_point.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-21 16:32:25+09:00




## Required by

* :heavy_check_mark: <a href="../../Graph/dinitz.cpp.html">最大流 (Dinitz) <small>(Graph/dinitz.cpp)</small></a>
* :question: <a href="../../Graph/scc.cpp.html">強連結成分分解 <small>(Graph/scc.cpp)</small></a>
* :question: <a href="../../Graph/two_sat.cpp.html">2-SAT <small>(Graph/two_sat.cpp)</small></a>
* :heavy_check_mark: <a href="../../algorithm/dp_on_tree.cpp.html">木 DP <small>(algorithm/dp_on_tree.cpp)</small></a>
* :question: <a href="../../algorithm/monotone_minima.cpp.html">monotone minima <small>(algorithm/monotone_minima.cpp)</small></a>
* :x: <a href="../../algorithm/online_to_offline_optimization.cpp.html">オンライン・オフライン変換 <small>(algorithm/online_to_offline_optimization.cpp)</small></a>


## Verified with

* :heavy_check_mark: <a href="../../../verify/test/aoj_1595.test.cpp.html">test/aoj_1595.test.cpp</a>
* :heavy_check_mark: <a href="../../../verify/test/aoj_2178.test.cpp.html">test/aoj_2178.test.cpp</a>
* :heavy_check_mark: <a href="../../../verify/test/aoj_2313.test.cpp.html">test/aoj_2313.test.cpp</a>
* :heavy_check_mark: <a href="../../../verify/test/aoj_2580.test.cpp.html">test/aoj_2580.test.cpp</a>
* :heavy_check_mark: <a href="../../../verify/test/aoj_2748.test.cpp.html">test/aoj_2748.test.cpp</a>
* :heavy_check_mark: <a href="../../../verify/test/aoj_2976.test.cpp.html">test/aoj_2976.test.cpp</a>
* :heavy_check_mark: <a href="../../../verify/test/aoj_ALDS1_10_A.test.cpp.html">test/aoj_ALDS1_10_A.test.cpp</a>
* :x: <a href="../../../verify/test/yc_703_onoff.test.cpp.html">test/yc_703_onoff.test.cpp</a>
* :x: <a href="../../../verify/test/yc_704_onoff.test.cpp.html">test/yc_704_onoff.test.cpp</a>
* :x: <a href="../../../verify/test/yc_705_onoff.test.cpp.html">test/yc_705_onoff.test.cpp</a>
* :x: <a href="../../../verify/test/yj_scc.test.cpp.html">test/yj_scc.test.cpp</a>
* :x: <a href="../../../verify/test/yj_two_sat.test.cpp.html">test/yj_two_sat.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
/**
 * @brief ラムダ式の再帰
 * @author えびちゃん
 */

#ifndef H_make_fix_point
#define H_make_fix_point

#include <utility>

template <typename Fn>
class fix_point: Fn {
public:
  explicit constexpr fix_point(Fn&& f) noexcept: Fn(std::forward<Fn>(f)) {}

  template <typename... Args>
  constexpr decltype(auto) operator ()(Args&&... args) const {
    return Fn::operator ()(*this, std::forward<Args>(args)...);
  }
};

template <typename Fn>
static inline constexpr decltype(auto) make_fix_point(Fn&& f) noexcept {
  return fix_point<Fn>{std::forward<Fn>(f)};
}

#endif  /* !defined(H_make_fix_point) */

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "utility/make/fix_point.cpp"
/**
 * @brief ラムダ式の再帰
 * @author えびちゃん
 */

#ifndef H_make_fix_point
#define H_make_fix_point

#include <utility>

template <typename Fn>
class fix_point: Fn {
public:
  explicit constexpr fix_point(Fn&& f) noexcept: Fn(std::forward<Fn>(f)) {}

  template <typename... Args>
  constexpr decltype(auto) operator ()(Args&&... args) const {
    return Fn::operator ()(*this, std::forward<Args>(args)...);
  }
};

template <typename Fn>
static inline constexpr decltype(auto) make_fix_point(Fn&& f) noexcept {
  return fix_point<Fn>{std::forward<Fn>(f)};
}

#endif  /* !defined(H_make_fix_point) */

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

