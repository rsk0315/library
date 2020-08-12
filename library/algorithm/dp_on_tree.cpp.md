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


# :warning: 木 DP <small>(algorithm/dp_on_tree.cpp)</small>

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#ed469618898d75b149e5c7c4b6a1c415">algorithm</a>
* <a href="{{ site.github.repository_url }}/blob/master/algorithm/dp_on_tree.cpp">View this file on GitHub</a>
    - Last commit date: 1970-01-01 00:00:00+00:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#ifndef H_dp_on_tree
#define H_dp_on_tree

/**
 * @brief 木 DP
 * @author えびちゃん
 */

#include <cstddef>
#include <utility>
#include <vector>

#include "utility/make/fix_point.cpp"

template <typename Monoid, typename AdjacencyList, typename Fn>
std::vector<Monoid> dp_on_tree(AdjacencyList const& g, Fn f, Monoid e = Monoid{}) {
  size_t n = g.size();
  std::vector<size_t> par(n, n);
  std::vector<std::vector<Monoid>> dpl(n), dpr(n);
  std::vector<Monoid> dp(n);
  for (size_t i = 0; i < n; ++i) {
    dpl[i].resize(g[i].size()+1, e);
    dpr[i].resize(g[i].size()+1, e);
  }

  make_fix_point([&](auto& dfs, size_t v, size_t p) -> Monoid {
    Monoid res = e;
    typename AdjacencyList::weight_type w{};
    for (size_t i = 0; i < g[v].size(); ++i) {
      auto const& e = g[v][i];
      size_t u = e.target();
      if (u == p) {
        par[v] = i;
        w = e.weight();
        continue;
      }
      Monoid tmp = dfs(u, v);
      res += tmp;
      dpl[v][i+1] = dpr[v][i] = tmp;
    }
    return f(res, w);
  })(0, n);

  make_fix_point([&](auto& dfs, size_t v, size_t p, size_t pi) -> void {
    if (p != n) {
      Monoid tmp = f(dpl[p][pi] + dpr[p][pi+1], g[p][pi].weight());
      dpl[v][par[v]+1] = dpr[v][par[v]] = tmp;
    }
    for (size_t i = 1; i < dpl[v].size(); ++i)
      dpl[v][i] = dpl[v][i-1] + std::move(dpl[v][i]);
    for (size_t i = dpr[v].size()-1; i--;)
      dpr[v][i] += dpr[v][i+1];

    dp[v] = dpr[v][0];
    for (size_t i = 0; i < g[v].size(); ++i){
      size_t u = g[v][i].target();
      if (u != p) dfs(u, v, i);
    }
  })(0, n, n);

  return dp;
}

#endif  /* !defined(H_dp_on_tree) */

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "algorithm/dp_on_tree.cpp"



/**
 * @brief 木 DP
 * @author えびちゃん
 */

#include <cstddef>
#include <utility>
#include <vector>

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
#line 14 "algorithm/dp_on_tree.cpp"

template <typename Monoid, typename AdjacencyList, typename Fn>
std::vector<Monoid> dp_on_tree(AdjacencyList const& g, Fn f, Monoid e = Monoid{}) {
  size_t n = g.size();
  std::vector<size_t> par(n, n);
  std::vector<std::vector<Monoid>> dpl(n), dpr(n);
  std::vector<Monoid> dp(n);
  for (size_t i = 0; i < n; ++i) {
    dpl[i].resize(g[i].size()+1, e);
    dpr[i].resize(g[i].size()+1, e);
  }

  make_fix_point([&](auto& dfs, size_t v, size_t p) -> Monoid {
    Monoid res = e;
    typename AdjacencyList::weight_type w{};
    for (size_t i = 0; i < g[v].size(); ++i) {
      auto const& e = g[v][i];
      size_t u = e.target();
      if (u == p) {
        par[v] = i;
        w = e.weight();
        continue;
      }
      Monoid tmp = dfs(u, v);
      res += tmp;
      dpl[v][i+1] = dpr[v][i] = tmp;
    }
    return f(res, w);
  })(0, n);

  make_fix_point([&](auto& dfs, size_t v, size_t p, size_t pi) -> void {
    if (p != n) {
      Monoid tmp = f(dpl[p][pi] + dpr[p][pi+1], g[p][pi].weight());
      dpl[v][par[v]+1] = dpr[v][par[v]] = tmp;
    }
    for (size_t i = 1; i < dpl[v].size(); ++i)
      dpl[v][i] = dpl[v][i-1] + std::move(dpl[v][i]);
    for (size_t i = dpr[v].size()-1; i--;)
      dpr[v][i] += dpr[v][i+1];

    dp[v] = dpr[v][0];
    for (size_t i = 0; i < g[v].size(); ++i){
      size_t u = g[v][i].target();
      if (u != p) dfs(u, v, i);
    }
  })(0, n, n);

  return dp;
}



```
{% endraw %}

<a href="../../index.html">Back to top page</a>

