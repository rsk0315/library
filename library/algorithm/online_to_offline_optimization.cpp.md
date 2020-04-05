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


# :x: オンライン・オフライン変換 <small>(algorithm/online_to_offline_optimization.cpp)</small>

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#ed469618898d75b149e5c7c4b6a1c415">algorithm</a>
* <a href="{{ site.github.repository_url }}/blob/master/algorithm/online_to_offline_optimization.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-06 04:52:14+09:00




## Depends on

* :question: <a href="monotone_minima.cpp.html">monotone minima <small>(algorithm/monotone_minima.cpp)</small></a>
* :question: <a href="../utility/limits.cpp.html">型依存の定数 <small>(utility/limits.cpp)</small></a>
* :question: <a href="../utility/make/fix_point.cpp.html">ラムダ式の再帰 <small>(utility/make/fix_point.cpp)</small></a>


## Verified with

* :x: <a href="../../verify/test/yc_703_onoff.test.cpp.html">test/yc_703_onoff.test.cpp</a>
* :x: <a href="../../verify/test/yc_704_onoff.test.cpp.html">test/yc_704_onoff.test.cpp</a>
* :x: <a href="../../verify/test/yc_705_onoff.test.cpp.html">test/yc_705_onoff.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#ifndef H_online_to_offline_optimization
#define H_online_to_offline_optimization

/**
 * @brief オンライン・オフライン変換
 * @author えびちゃん
 */

#include <cstddef>
#include <algorithm>
#include <vector>

#include "algorithm/monotone_minima.cpp"
#include "utility/limits.cpp"
#include "utility/make/fix_point.cpp"

template <typename Fn>
auto online_to_offline_optimization(Fn&& f, size_t n, decltype(f(n, n)) init = 0) {
  // FIXME: コスト関数 f を渡すんじゃなくて induce を渡す設計にしたいかも。
  //        SMAWK で解きたいとか、別の性質が使えるとかありそう。
  //        よさげなインタフェースが思いついたら変更する。

  using value_type = decltype(f(n, n));
  std::vector<value_type> dp(n, limits<value_type>::max());
  dp[0] = init;

  auto induce = [&](size_t l, size_t m, size_t r) -> void {
    auto g = [&](size_t i, size_t j) -> value_type {
      return dp[j+l] + f(j+l, i+m);
    };
    auto argmin = monotone_minima(g, r-m, m-l);
    for (size_t i = m; i < r; ++i) {
      size_t j = argmin[i-m] + l;
      dp[i] = std::min(dp[i], g(i-m, j-l));
    }
  };

  make_fix_point([&](auto& solve, size_t l, size_t r) -> void {
      if (l+1 == r) {
        if (r < n) dp[r] = std::min(dp[r], dp[l] + f(l, r));
        return;
      }
      size_t m = (l+r) >> 1;
      solve(l, m);
      induce(l, m, r);
      solve(m, r);
  })(0, n);
  return dp;
}

#endif  /* !defined(H_online_to_offline_optimization) */

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "algorithm/online_to_offline_optimization.cpp"



/**
 * @brief オンライン・オフライン変換
 * @author えびちゃん
 */

#include <cstddef>
#include <algorithm>
#include <vector>

#line 1 "algorithm/monotone_minima.cpp"



/**
 * @brief monotone minima
 * @author えびちゃん
 */

#line 10 "algorithm/monotone_minima.cpp"
#include <utility>
#line 12 "algorithm/monotone_minima.cpp"

#line 1 "utility/make/fix_point.cpp"
/**
 * @brief ラムダ式の再帰
 * @author えびちゃん
 */

#ifndef H_make_fix_point
#define H_make_fix_point

#line 10 "utility/make/fix_point.cpp"

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
#line 14 "algorithm/monotone_minima.cpp"

template <typename Fn>
auto monotone_minima(Fn&& f, size_t h, size_t w) {
  using value_type = decltype(f(h, w));
  std::vector<size_t> res(h);

  make_fix_point([&](auto dfs, size_t hl, size_t hu, size_t wl, size_t wu) -> void {
      if (hl >= hu) return;
      size_t hm = (hl+hu) >> 1;
      value_type min = f(hm, wl);
      res[hm] = wl;
      for (size_t j = wl+1; j < wu; ++j) {
        value_type cur = f(hm, j);
        if (cur < min) {
          min = std::move(cur);
          res[hm] = j;
        }
      }
      if (hl == hm) return;
      dfs(hl, hm, wl, res[hm]+1);
      dfs(hm+1, hu, res[hm], wu);
  })(0, h, 0, w);
  return res;
}


#line 1 "utility/limits.cpp"
/**
 * @brief 型依存の定数
 * @author えびちゃん
 */

#include <limits>

#ifndef H_limits
#define H_limits

template <typename Tp>
class limits: public std::numeric_limits<Tp> {};

#endif  /* !defined(H_limits) */
#line 1 "utility/make/fix_point.cpp"
/**
 * @brief ラムダ式の再帰
 * @author えびちゃん
 */

#ifndef H_make_fix_point
#define H_make_fix_point

#line 10 "utility/make/fix_point.cpp"

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
#line 16 "algorithm/online_to_offline_optimization.cpp"

template <typename Fn>
auto online_to_offline_optimization(Fn&& f, size_t n, decltype(f(n, n)) init = 0) {
  // FIXME: コスト関数 f を渡すんじゃなくて induce を渡す設計にしたいかも。
  //        SMAWK で解きたいとか、別の性質が使えるとかありそう。
  //        よさげなインタフェースが思いついたら変更する。

  using value_type = decltype(f(n, n));
  std::vector<value_type> dp(n, limits<value_type>::max());
  dp[0] = init;

  auto induce = [&](size_t l, size_t m, size_t r) -> void {
    auto g = [&](size_t i, size_t j) -> value_type {
      return dp[j+l] + f(j+l, i+m);
    };
    auto argmin = monotone_minima(g, r-m, m-l);
    for (size_t i = m; i < r; ++i) {
      size_t j = argmin[i-m] + l;
      dp[i] = std::min(dp[i], g(i-m, j-l));
    }
  };

  make_fix_point([&](auto& solve, size_t l, size_t r) -> void {
      if (l+1 == r) {
        if (r < n) dp[r] = std::min(dp[r], dp[l] + f(l, r));
        return;
      }
      size_t m = (l+r) >> 1;
      solve(l, m);
      induce(l, m, r);
      solve(m, r);
  })(0, n);
  return dp;
}



```
{% endraw %}

<a href="../../index.html">Back to top page</a>

