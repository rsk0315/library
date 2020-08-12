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


# :warning: 2-SAT <small>(Graph/two_sat.cpp)</small>

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#4cdbd2bafa8193091ba09509cedf94fd">Graph</a>
* <a href="{{ site.github.repository_url }}/blob/master/Graph/two_sat.cpp">View this file on GitHub</a>
    - Last commit date: 1970-01-01 00:00:00+00:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#ifndef H_two_sat
#define H_two_sat

/**
 * @brief 2-SAT
 * @author えびちゃん
 */

#include <cstddef>
#include <vector>

#include "Graph/adjacency_list.cpp"
#include "Graph/scc.cpp"

class two_sat {
public:
  using size_type = size_t;

private:
  size_type M_n;
  adjacency_list<weighted_edge<bool>, directed_tag> M_g;
  std::vector<size_type> M_scc;
  bool M_sat;

  void M_solve() {
    if (!M_scc.empty()) return;
    M_scc = strongly_connected_components(M_g);
    for (size_type i = 0; i < M_n; ++i)
      if (M_scc[i] == M_scc[i+M_n]) {
        M_sat = false;
        return;
      }
    M_sat = true;
  }

public:
  two_sat() = default;
  explicit two_sat(size_type n): M_n(n), M_g(n+n) {}

  void push(size_type i, bool bi, size_type j, bool bj) {
    M_scc.clear();

    size_type not_i = i + M_n;
    size_type not_j = j + M_n;
    if (!bi) std::swap(i, not_i);
    if (!bj) std::swap(j, not_j);

    // i or j, (not i => j, not j => i)
    M_g.emplace(not_i, j, 1);
    M_g.emplace(not_j, i, 1);
  }

  bool satisfiable() {
    M_solve();
    return M_sat;    
  }

  bool operator [](size_type i) {
    M_solve();
    return M_scc[i+M_n] < M_scc[i];
  }
};

#endif  /* !defined(H_two_sat) */

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "Graph/two_sat.cpp"



/**
 * @brief 2-SAT
 * @author えびちゃん
 */

#include <cstddef>
#include <vector>

#line 1 "Graph/adjacency_list.cpp"



/**
 * @brief 重みつきグラフの隣接リスト
 * @author えびちゃん
 */

#line 10 "Graph/adjacency_list.cpp"
#include <algorithm>
#include <type_traits>
#line 13 "Graph/adjacency_list.cpp"

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


#line 1 "Graph/scc.cpp"



/**
 * @brief 強連結成分分解
 * @author えびちゃん
 */

#line 11 "Graph/scc.cpp"

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
#line 14 "Graph/scc.cpp"

template <typename AdjacencyList>
auto strongly_connected_components(AdjacencyList const& g) {
  size_t n = g.size();
  adjacency_list<weighted_edge<bool>, directed_tag> h(n);
  for (size_t v = 0; v < n; ++v)
    for (auto const& e: g[v]) h.emplace(e.target(), e.source(), 1);

  std::vector<bool> used(n);
  std::vector<size_t> vs;
  auto dfs = make_fix_point([&](auto f, size_t v) -> void {
      used[v] = true;
      for (auto const& e: g[v])
        if (!used[e.target()]) f(e.target());
      vs.push_back(v);
  });
  for (size_t v = 0; v < n; ++v)
    if (!used[v]) dfs(v);

  used.assign(n, false);
  std::vector<size_t> cmp(n);
  size_t num = 0;
  auto rdfs = make_fix_point([&](auto f, size_t v) -> void {
      used[v] = true;
      cmp[v] = num;
      for (auto const& e: h[v])
        if (!used[e.target()]) f(e.target());
  });
  for (size_t v = vs.size(); v--;)
    if (!used[vs[v]])
      rdfs(vs[v]), ++num;

  return cmp;
}


#line 14 "Graph/two_sat.cpp"

class two_sat {
public:
  using size_type = size_t;

private:
  size_type M_n;
  adjacency_list<weighted_edge<bool>, directed_tag> M_g;
  std::vector<size_type> M_scc;
  bool M_sat;

  void M_solve() {
    if (!M_scc.empty()) return;
    M_scc = strongly_connected_components(M_g);
    for (size_type i = 0; i < M_n; ++i)
      if (M_scc[i] == M_scc[i+M_n]) {
        M_sat = false;
        return;
      }
    M_sat = true;
  }

public:
  two_sat() = default;
  explicit two_sat(size_type n): M_n(n), M_g(n+n) {}

  void push(size_type i, bool bi, size_type j, bool bj) {
    M_scc.clear();

    size_type not_i = i + M_n;
    size_type not_j = j + M_n;
    if (!bi) std::swap(i, not_i);
    if (!bj) std::swap(j, not_j);

    // i or j, (not i => j, not j => i)
    M_g.emplace(not_i, j, 1);
    M_g.emplace(not_j, i, 1);
  }

  bool satisfiable() {
    M_solve();
    return M_sat;    
  }

  bool operator [](size_type i) {
    M_solve();
    return M_scc[i+M_n] < M_scc[i];
  }
};



```
{% endraw %}

<a href="../../index.html">Back to top page</a>

