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


# :heavy_check_mark: test/yj_lca_squaring.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/yj_lca_squaring.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-06 05:07:20+09:00


* see: <a href="https://judge.yosupo.jp/problem/lca">https://judge.yosupo.jp/problem/lca</a>


## Depends on

* :heavy_check_mark: <a href="../../library/Graph/adjacency_list.cpp.html">重みつきグラフの隣接リスト <small>(Graph/adjacency_list.cpp)</small></a>
* :heavy_check_mark: <a href="../../library/Graph/lowest_common_ancestor_squaring.cpp.html">最深共通祖先 (squaring) <small>(Graph/lowest_common_ancestor_squaring.cpp)</small></a>
* :heavy_check_mark: <a href="../../library/utility/literals.cpp.html">ユーザ定義リテラル <small>(utility/literals.cpp)</small></a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/lca"

#include <cstdio>

#include "Graph/adjacency_list.cpp"
#include "Graph/lowest_common_ancestor_squaring.cpp"

int main() {
  size_t n, q;
  scanf("%zu %zu", &n, &q);

  adjacency_list<weighted_edge<int>, undirected_tag> g(n);
  for (size_t i = 1; i < n; ++i) {
    size_t p;
    scanf("%zu", &p);
    g.emplace(i, p, 1);
  }

  lowest_common_ancestor lca(g, 0);
  for (size_t i = 0; i < q; ++i) {
    size_t u, v;
    scanf("%zu %zu", &u, &v);
    printf("%zu\n", lca(u, v));
  }
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/yj_lca_squaring.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/lca"

#include <cstdio>

#line 1 "Graph/adjacency_list.cpp"



/**
 * @brief 重みつきグラフの隣接リスト
 * @author えびちゃん
 */

#include <cstddef>
#include <algorithm>
#include <type_traits>
#include <vector>

template <typename WeightType>
class weighted_edge {
public:
  using size_type = size_t;
  using weight_type = WeightType;

protected:
  size_type M_src, M_dst;
  weight_type M_weight;

public:
  weighted_edge() = default;
  weighted_edge(weighted_edge const&) = default;
  weighted_edge(weighted_edge&&) = default;

  weighted_edge(size_type s, size_type d, weight_type w):
    M_src(s), M_dst(d), M_weight(w)
  {}

  weighted_edge& operator =(weighted_edge const&) = default;
  weighted_edge& operator =(weighted_edge&&) = default;

  bool operator <(weighted_edge const& other) const {
    if (M_weight < other.M_weight) return true;
    if (other.M_weight < M_weight) return false;
    if (M_src != other.M_src) return M_src < other.M_src;
    return M_dst < other.M_dst;
  }

  size_type source() const { return M_src; }
  size_type target() const { return M_dst; }
  weight_type weight() const { return M_weight; }
};

struct directed_tag {};
struct undirected_tag {};

template <typename Edge, typename Directedness>
class adjacency_list {
public:
  using size_type = size_t;
  using edge_type = Edge;
  using weight_type = typename Edge::weight_type;

private:
  std::vector<std::vector<edge_type>> M_g;

public:
  adjacency_list() = default;
  adjacency_list(adjacency_list const&) = default;
  adjacency_list(adjacency_list&&) = default;
  explicit adjacency_list(size_type n): M_g(n) {}

  template <typename... Args>
  void emplace(size_type src, size_type dst, Args... args) {
    M_g[src].emplace_back(src, dst, args...);
    if (std::is_same<Directedness, undirected_tag>::value)
      M_g[dst].emplace_back(dst, src, args...);
  }

  void sort_by_index() {
    auto cmp = [](auto const& e1, auto const& e2) {
      return e1.target() < e2.target();
    };
    for (auto v: M_g) std::sort(v.begin(), v.end(), cmp);
  }

  size_type size() const { return M_g.size(); }
  auto const& operator [](size_type i) const { return M_g[i]; }
};


#line 1 "Graph/lowest_common_ancestor_squaring.cpp"



/**
 * @brief 最深共通祖先 (squaring)
 * @author えびちゃん
 */

#line 11 "Graph/lowest_common_ancestor_squaring.cpp"
#include <tuple>
#include <utility>
#line 14 "Graph/lowest_common_ancestor_squaring.cpp"

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


#line 7 "test/yj_lca_squaring.test.cpp"

int main() {
  size_t n, q;
  scanf("%zu %zu", &n, &q);

  adjacency_list<weighted_edge<int>, undirected_tag> g(n);
  for (size_t i = 1; i < n; ++i) {
    size_t p;
    scanf("%zu", &p);
    g.emplace(i, p, 1);
  }

  lowest_common_ancestor lca(g, 0);
  for (size_t i = 0; i < q; ++i) {
    size_t u, v;
    scanf("%zu %zu", &u, &v);
    printf("%zu\n", lca(u, v));
  }
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

