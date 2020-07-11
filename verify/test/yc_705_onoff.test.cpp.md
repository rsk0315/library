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


# :heavy_check_mark: test/yc_705_onoff.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/yc_705_onoff.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-07-11 14:49:45+09:00


* see: <a href="https://yukicoder.me/problems/no/705">https://yukicoder.me/problems/no/705</a>


## Depends on

* :heavy_check_mark: <a href="../../library/algorithm/monotone_minima.cpp.html">monotone minima <small>(algorithm/monotone_minima.cpp)</small></a>
* :heavy_check_mark: <a href="../../library/algorithm/online_to_offline_optimization.cpp.html">オンライン・オフライン変換 <small>(algorithm/online_to_offline_optimization.cpp)</small></a>
* :heavy_check_mark: <a href="../../library/utility/limits.cpp.html">型依存の定数 <small>(utility/limits.cpp)</small></a>
* :heavy_check_mark: <a href="../../library/utility/make/fix_point.cpp.html">ラムダ式の再帰 <small>(utility/make/fix_point.cpp)</small></a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://yukicoder.me/problems/no/705"

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>

#include "algorithm/online_to_offline_optimization.cpp"

int main() {
  size_t n;
  scanf("%zu", &n);

  std::vector<int> a(n), x(n), y(n);
  for (auto& ai: a) scanf("%d", &ai);
  for (auto& xi: x) scanf("%d", &xi);
  for (auto& yi: y) scanf("%d", &yi);

  auto f = [&](size_t j, size_t i) {
    intmax_t dx = x[j] - a[i-1];
    intmax_t dy = y[j];
    return std::abs(dx)*dx*dx + std::abs(dy)*dy*dy;
  };

  auto dp = online_to_offline_optimization(f, n+1);
  printf("%jd\n", dp[n]);
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/yc_705_onoff.test.cpp"
#define PROBLEM "https://yukicoder.me/problems/no/705"

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>

#line 1 "algorithm/online_to_offline_optimization.cpp"



/**
 * @brief オンライン・オフライン変換
 * @author えびちゃん
 */

#include <cstddef>
#line 12 "algorithm/online_to_offline_optimization.cpp"

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
#line 11 "utility/limits.cpp"

template <typename Tp>
class limits: public std::numeric_limits<Tp> {};

template <typename T1, typename T2>
class limits<std::pair<T1, T2>> {
public:
  static constexpr auto min() {
    return std::make_pair(limits<T1>::min(), limits<T2>::min());
  }
  static constexpr auto max() {
    return std::make_pair(limits<T1>::max(), limits<T2>::max());
  }
};


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


#line 10 "test/yc_705_onoff.test.cpp"

int main() {
  size_t n;
  scanf("%zu", &n);

  std::vector<int> a(n), x(n), y(n);
  for (auto& ai: a) scanf("%d", &ai);
  for (auto& xi: x) scanf("%d", &xi);
  for (auto& yi: y) scanf("%d", &yi);

  auto f = [&](size_t j, size_t i) {
    intmax_t dx = x[j] - a[i-1];
    intmax_t dy = y[j];
    return std::abs(dx)*dx*dx + std::abs(dy)*dy*dy;
  };

  auto dp = online_to_offline_optimization(f, n+1);
  printf("%jd\n", dp[n]);
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

