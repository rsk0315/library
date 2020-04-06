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


# :question: 最深共通祖先 (squaring) <small>(Graph/lowest_common_ancestor_squaring.cpp)</small>

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#4cdbd2bafa8193091ba09509cedf94fd">Graph</a>
* <a href="{{ site.github.repository_url }}/blob/master/Graph/lowest_common_ancestor_squaring.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-06 04:52:14+09:00




## Depends on

* :question: <a href="../utility/literals.cpp.html">ユーザ定義リテラル <small>(utility/literals.cpp)</small></a>


## Verified with

* :x: <a href="../../verify/test/aoj_GRL_5_C_squaring.test.cpp.html">test/aoj_GRL_5_C_squaring.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yj_lca_squaring.test.cpp.html">test/yj_lca_squaring.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#ifndef H_lowest_common_ancestor_squaring
#define H_lowest_common_ancestor_squaring

/**
 * @brief 最深共通祖先 (squaring)
 * @author えびちゃん
 */

#include <cstddef>
#include <algorithm>
#include <tuple>
#include <utility>
#include <vector>

#include "utility/literals.cpp"

class lowest_common_ancestor {
public:
  using size_type = size_t;

private:
  std::vector<size_type> M_d;
  std::vector<std::vector<size_type>> M_p;

  template <typename Tree>
  void M_dfs(Tree const& g, size_type v, size_type p) {
    for (auto const& e: g[v]) {
      size_type u = e.target();
      if (u == p) continue;
      M_p[0][u] = v;
      M_d[u] = M_d[v] + 1;
      M_dfs(g, u, v);
    }
  }

  void M_double() {
    size_type n = M_p[0].size();
    while (true) {
      bool valid = false;
      auto const& back = M_p.back();
      std::vector<size_type> tmp(n, -1);
      for (size_type i = 0; i < n; ++i) {
        if (back[i] == -1_zu) continue;
        tmp[i] = back[back[i]];
        if (tmp[i] != -1_zu) valid = true;
      }
      if (!valid) break;
      M_p.push_back(std::move(tmp));
    }
  }

public:
  lowest_common_ancestor() = default;
  lowest_common_ancestor(lowest_common_ancestor const&) = default;
  lowest_common_ancestor(lowest_common_ancestor&&) = default;

  template <typename Tree>
  lowest_common_ancestor(Tree const& g, size_type r) {
    size_type n = g.size();
    M_d.assign(n, 0);
    M_p.emplace_back(n, -1);
    M_dfs(g, r, -1);
    M_double();
  }

  lowest_common_ancestor& operator =(lowest_common_ancestor const&) = default;
  lowest_common_ancestor& operator =(lowest_common_ancestor&&) = default;

  size_type operator ()(size_type u, size_type v) const {
    if (M_d[u] > M_d[v]) std::swap(u, v);
    if (M_d[u] < M_d[v]) {
      size_type d = M_d[v] - M_d[u];
      for (size_type i = 0; i < M_p.size(); ++i)
        if (d >> i & 1) v = M_p[i][v];
    }
    if (u == v) return u;
    for (size_type i = M_p.size(); i--;) {
      if (M_p[i][u] == M_p[i][v]) continue;
      u = M_p[i][u];
      v = M_p[i][v];
    }
    return M_p[0][u];
  }
};

#endif  /* !defined(H_lowest_common_ancestor_squaring) */

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "Graph/lowest_common_ancestor_squaring.cpp"



/**
 * @brief 最深共通祖先 (squaring)
 * @author えびちゃん
 */

#include <cstddef>
#include <algorithm>
#include <tuple>
#include <utility>
#include <vector>

#line 1 "utility/literals.cpp"



/**
 * @brief ユーザ定義リテラル
 * @author えびちゃん
 */

#line 10 "utility/literals.cpp"
#include <cstdint>

constexpr intmax_t  operator ""_jd(unsigned long long n) { return n; }
constexpr uintmax_t operator ""_ju(unsigned long long n) { return n; }
constexpr size_t    operator ""_zu(unsigned long long n) { return n; }
constexpr ptrdiff_t operator ""_td(unsigned long long n) { return n; }


#line 16 "Graph/lowest_common_ancestor_squaring.cpp"

class lowest_common_ancestor {
public:
  using size_type = size_t;

private:
  std::vector<size_type> M_d;
  std::vector<std::vector<size_type>> M_p;

  template <typename Tree>
  void M_dfs(Tree const& g, size_type v, size_type p) {
    for (auto const& e: g[v]) {
      size_type u = e.target();
      if (u == p) continue;
      M_p[0][u] = v;
      M_d[u] = M_d[v] + 1;
      M_dfs(g, u, v);
    }
  }

  void M_double() {
    size_type n = M_p[0].size();
    while (true) {
      bool valid = false;
      auto const& back = M_p.back();
      std::vector<size_type> tmp(n, -1);
      for (size_type i = 0; i < n; ++i) {
        if (back[i] == -1_zu) continue;
        tmp[i] = back[back[i]];
        if (tmp[i] != -1_zu) valid = true;
      }
      if (!valid) break;
      M_p.push_back(std::move(tmp));
    }
  }

public:
  lowest_common_ancestor() = default;
  lowest_common_ancestor(lowest_common_ancestor const&) = default;
  lowest_common_ancestor(lowest_common_ancestor&&) = default;

  template <typename Tree>
  lowest_common_ancestor(Tree const& g, size_type r) {
    size_type n = g.size();
    M_d.assign(n, 0);
    M_p.emplace_back(n, -1);
    M_dfs(g, r, -1);
    M_double();
  }

  lowest_common_ancestor& operator =(lowest_common_ancestor const&) = default;
  lowest_common_ancestor& operator =(lowest_common_ancestor&&) = default;

  size_type operator ()(size_type u, size_type v) const {
    if (M_d[u] > M_d[v]) std::swap(u, v);
    if (M_d[u] < M_d[v]) {
      size_type d = M_d[v] - M_d[u];
      for (size_type i = 0; i < M_p.size(); ++i)
        if (d >> i & 1) v = M_p[i][v];
    }
    if (u == v) return u;
    for (size_type i = M_p.size(); i--;) {
      if (M_p[i][u] == M_p[i][v]) continue;
      u = M_p[i][u];
      v = M_p[i][v];
    }
    return M_p[0][u];
  }
};



```
{% endraw %}

<a href="../../index.html">Back to top page</a>

