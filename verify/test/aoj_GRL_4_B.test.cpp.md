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


# :x: test/aoj_GRL_4_B.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/aoj_GRL_4_B.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-31 04:28:06+09:00




## Depends on

* :question: <a href="../../library/Graph/adjacency_list.cpp.html">重みつきグラフの隣接リスト <small>(Graph/adjacency_list.cpp)</small></a>
* :x: <a href="../../library/Graph/topological_sort.cpp.html">トポロジカルソート <small>(Graph/topological_sort.cpp)</small></a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_4_B" 
#define IGNORE  /* requires a special judge */

#define CALL_FROM_TEST
#include "Graph/adjacency_list.cpp"
#include "Graph/topological_sort.cpp"
#undef CALL_FROM_TEST

#include <cstdio>

int main() {
  size_t n, m;
  scanf("%zu %zu", &n, &m);

  adjacency_list<weighted_edge<int>, directed_tag> g(n);
  for (size_t i = 0; i < m; ++i) {
    size_t u, v;
    scanf("%zu %zu", &u, &v);
    g.emplace(u, v, 1);
  }

  auto ord = topological_sort(g);
  for (size_t i = 0; i < n; ++i)
    printf("%zu\n", ord[i]);
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/aoj_GRL_4_B.test.cpp"
#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_4_B" 
#define IGNORE  /* requires a special judge */

#define CALL_FROM_TEST
#line 1 "Graph/adjacency_list.cpp"
/**
 * @brief 重みつきグラフの隣接リスト
 * @author えびちゃん
 */

#ifndef H_adjacency_list
#define H_adjacency_list

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

#endif  /* !defined(H_adjacency_list) */
#line 1 "Graph/topological_sort.cpp"
/**
 * @brief トポロジカルソート
 * @author えびちゃん
 */

#ifndef H_topological_sort
#define H_topological_sort

#include <queue>
#include <vector>

template <typename AdjacencyList>
std::vector<size_t> topological_sort(AdjacencyList const& g) {
  size_t n = g.size();
  std::vector<size_t> ord, indeg(n, 0);
  std::queue<size_t> q;
  ord.reserve(n);
  for (size_t v = 0; v < n; ++v)
    for (auto const& e: g[v]) ++indeg[e.target()];
  for (size_t v = 0; v < n; ++v)
    if (indeg[v] == 0) q.push(v);
  while (!q.empty()) {
    size_t v = q.front();
    q.pop();
    ord.push_back(v);
    for (auto const& e: g[v]) {
      size_t u = e.target();
      if (--indeg[u] == 0) q.push(u);
    }
  }
  if (ord.size() < n) ord.clear();
  return ord;
}

#endif  /* !defined(H_topological_sort) */
#line 7 "test/aoj_GRL_4_B.test.cpp"
#undef CALL_FROM_TEST

#include <cstdio>

int main() {
  size_t n, m;
  scanf("%zu %zu", &n, &m);

  adjacency_list<weighted_edge<int>, directed_tag> g(n);
  for (size_t i = 0; i < m; ++i) {
    size_t u, v;
    scanf("%zu %zu", &u, &v);
    g.emplace(u, v, 1);
  }

  auto ord = topological_sort(g);
  for (size_t i = 0; i < n; ++i)
    printf("%zu\n", ord[i]);
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

