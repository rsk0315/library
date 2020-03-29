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


# :heavy_check_mark: 木 DP <small>(algorithm/dp_on_tree.cpp)</small>

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#ed469618898d75b149e5c7c4b6a1c415">algorithm</a>
* <a href="{{ site.github.repository_url }}/blob/master/algorithm/dp_on_tree.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-30 03:19:46+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/test/aoj_1595.test.cpp.html">test/aoj_1595.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
/**
 * @brief 木 DP
 * @author えびちゃん
 */

#ifndef H_dp_on_tree
#define H_dp_on_tree

#include <cstddef>
#include <queue>
#include <vector>

template <typename Monoid, typename AdjacencyList, typename Fn>
std::vector<Monoid> dp_on_tree(AdjacencyList const& g, Fn f) {
  size_t n = g.size();
  std::vector<size_t> ord, par(n, n);
  std::vector<bool> vis(n, false);
  ord.reserve(n);
  vis[0] = true;
  std::queue<size_t> q;
  q.push(0);
  while (!q.empty()) {
    size_t v = q.front();
    q.pop();
    ord.push_back(v);
    for (auto const& e: g[v]) {
      size_t u = e.target();
      if (!vis[u]) {
        vis[u] = true;
        par[u] = v;
        q.push(u);
      }
    }
  }

  Monoid e{};
  std::vector<Monoid> dpl(n, e), dpr(n, e), dpp(n, e);
  for (size_t i = n; i--;) {
    size_t v = ord[i];
    bool bef = true;
    for (size_t j = 0; j < g[v].size(); ++j) {
      auto const& e = g[v][j];
      size_t u = e.target();
      auto w = e.weight();
      if (u == par[v]) {
        bef = true;
      } else if (bef) {
        dpl[v] += f(dpl[u] + dpr[u], w);
      } else {
        dpr[v] = f(dpl[u] + dpr[u], w) + std::move(dpr[v]);
      }
    }
  }

  std::vector<Monoid> dp(n);
  for (size_t i = 0; i < n; ++i) {
    size_t v = ord[i];
    std::vector<Monoid> al(g[v].size());
    for (size_t j = 0; j < g[v].size(); ++j) {
      auto const& e = g[v][j];
      size_t u = e.target();
      auto w = e.weight();
      al[j] = ((u == par[v])? dpp[v]: f(dpl[u] + dpr[u], w));
    }
    auto ar = al;
    al.insert(al.begin(), e);
    ar.push_back(e);
    for (size_t j = 1; j <= g[v].size(); ++j) al[j] = al[j-1] + std::move(al[j]);
    for (size_t j = g[v].size(); j--;) ar[j] += ar[j+1];
    for (size_t j = 0; j < g[v].size(); ++j) {
      auto const& e = g[v][j];
      size_t u = e.target();
      if (u == par[v]) continue;
      auto w = e.weight();
      dpp[u] = f(al[j] + ar[j+1], w);
    }
    dp[v] = ar[0];
  }
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

#ifndef H_dp_on_tree
#define H_dp_on_tree

#include <cstddef>
#include <queue>
#include <vector>

template <typename Monoid, typename AdjacencyList, typename Fn>
std::vector<Monoid> dp_on_tree(AdjacencyList const& g, Fn f) {
  size_t n = g.size();
  std::vector<size_t> ord, par(n, n);
  std::vector<bool> vis(n, false);
  ord.reserve(n);
  vis[0] = true;
  std::queue<size_t> q;
  q.push(0);
  while (!q.empty()) {
    size_t v = q.front();
    q.pop();
    ord.push_back(v);
    for (auto const& e: g[v]) {
      size_t u = e.target();
      if (!vis[u]) {
        vis[u] = true;
        par[u] = v;
        q.push(u);
      }
    }
  }

  Monoid e{};
  std::vector<Monoid> dpl(n, e), dpr(n, e), dpp(n, e);
  for (size_t i = n; i--;) {
    size_t v = ord[i];
    bool bef = true;
    for (size_t j = 0; j < g[v].size(); ++j) {
      auto const& e = g[v][j];
      size_t u = e.target();
      auto w = e.weight();
      if (u == par[v]) {
        bef = true;
      } else if (bef) {
        dpl[v] += f(dpl[u] + dpr[u], w);
      } else {
        dpr[v] = f(dpl[u] + dpr[u], w) + std::move(dpr[v]);
      }
    }
  }

  std::vector<Monoid> dp(n);
  for (size_t i = 0; i < n; ++i) {
    size_t v = ord[i];
    std::vector<Monoid> al(g[v].size());
    for (size_t j = 0; j < g[v].size(); ++j) {
      auto const& e = g[v][j];
      size_t u = e.target();
      auto w = e.weight();
      al[j] = ((u == par[v])? dpp[v]: f(dpl[u] + dpr[u], w));
    }
    auto ar = al;
    al.insert(al.begin(), e);
    ar.push_back(e);
    for (size_t j = 1; j <= g[v].size(); ++j) al[j] = al[j-1] + std::move(al[j]);
    for (size_t j = g[v].size(); j--;) ar[j] += ar[j+1];
    for (size_t j = 0; j < g[v].size(); ++j) {
      auto const& e = g[v][j];
      size_t u = e.target();
      if (u == par[v]) continue;
      auto w = e.weight();
      dpp[u] = f(al[j] + ar[j+1], w);
    }
    dp[v] = ar[0];
  }
  return dp;
}

#endif  /* !defined(H_dp_on_tree) */

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

