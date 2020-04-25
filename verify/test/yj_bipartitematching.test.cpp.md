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


# :heavy_check_mark: test/yj_bipartitematching.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/yj_bipartitematching.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-24 10:01:40+09:00


* see: <a href="https://judge.yosupo.jp/problem/bipartitematching">https://judge.yosupo.jp/problem/bipartitematching</a>


## Depends on

* :heavy_check_mark: <a href="../../library/Graph/adjacency_list.cpp.html">重みつきグラフの隣接リスト <small>(Graph/adjacency_list.cpp)</small></a>
* :heavy_check_mark: <a href="../../library/Graph/capacitated_adjacency_list.cpp.html">容量つきグラフの隣接リスト <small>(Graph/capacitated_adjacency_list.cpp)</small></a>
* :heavy_check_mark: <a href="../../library/Graph/dinitz.cpp.html">最大流 (Dinitz 法) <small>(Graph/dinitz.cpp)</small></a>
* :heavy_check_mark: <a href="../../library/utility/limits.cpp.html">型依存の定数 <small>(utility/limits.cpp)</small></a>
* :heavy_check_mark: <a href="../../library/utility/literals.cpp.html">ユーザ定義リテラル <small>(utility/literals.cpp)</small></a>
* :heavy_check_mark: <a href="../../library/utility/make/fix_point.cpp.html">ラムダ式の再帰 <small>(utility/make/fix_point.cpp)</small></a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/bipartitematching"

#include <cstdio>
#include <vector>

#include "Graph/capacitated_adjacency_list.cpp"
#include "Graph/dinitz.cpp"

int main() {
  size_t l, r, m;
  scanf("%zu %zu %zu", &l, &r, &m);

  adjacency_list<capacitated_edge<int>, directed_tag> g(l+r+2);
  size_t source = l+r;
  size_t sink = source+1;
  for (size_t i = 0; i < m; ++i) {
    size_t a, b;
    scanf("%zu %zu", &a, &b);
    g.emplace(a, l+b, 1);
  }

  for (size_t i = 0; i < l; ++i) g.emplace(source, i, 1);
  for (size_t i = 0; i < r; ++i) g.emplace(l+i, sink, 1);

  printf("%d\n", max_flow(g, source, sink, dinitz));

  for (size_t i = 0; i < l; ++i) {
    for (auto const& e: g[i]) {
      size_t j = e.target();
      if (j == source) continue;
      if (e.capacity() == 0) printf("%zu %zu\n", i, j-l);
    }
  }
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/yj_bipartitematching.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/bipartitematching"

#include <cstdio>
#include <vector>

#line 1 "Graph/capacitated_adjacency_list.cpp"



/**
 * @brief 容量つきグラフの隣接リスト
 * @author えびちゃん
 */

#include <cstddef>

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


#line 12 "Graph/capacitated_adjacency_list.cpp"

template <typename WeightType>
class capacitated_edge {
public:
  using size_type = size_t;
  using weight_type = WeightType;

protected:
  size_type M_src, M_dst;
  weight_type M_capacity;
  size_type M_rev;

public:
  capacitated_edge() = default;
  capacitated_edge(capacitated_edge const&) = default;
  capacitated_edge(capacitated_edge&&) = default;

  capacitated_edge(size_type s, size_type d, weight_type c, size_type r):
    M_src(s), M_dst(d), M_capacity(c), M_rev(r)
  {}

  capacitated_edge& operator =(capacitated_edge const&) = default;
  capacitated_edge& operator =(capacitated_edge&&) = default;

  bool operator <(capacitated_edge const& other) const {
    if (M_capacity < other.M_capacity) return true;
    if (other.M_capacity < M_capacity) return false;
    if (M_src != other.M_src) return M_src < other.M_src;
    return M_dst < other.M_dst;
  }

  size_type source() const { return M_src; }
  size_type target() const { return M_dst; }
  weight_type capacity() const { return M_capacity; }
  weight_type& capacity() { return M_capacity; }
  size_type reversed() const { return M_rev; }
};

template <typename WeightType, typename Directedness>
class adjacency_list<capacitated_edge<WeightType>, Directedness> {
public:
  using size_type = size_t;
  using edge_type = capacitated_edge<WeightType>;
  using weight_type = WeightType;

private:
  std::vector<std::vector<edge_type>> M_g;

public:
  adjacency_list() = default;
  adjacency_list(adjacency_list const&) = default;
  adjacency_list(adjacency_list&&) = default;
  explicit adjacency_list(size_type n): M_g(n) {}

  template <typename... Args>
  void emplace(size_type src, size_type dst, weight_type cap) {
    M_g[src].emplace_back(src, dst, cap, M_g[dst].size());
    if (std::is_same<Directedness, directed_tag>::value) {
      M_g[dst].emplace_back(dst, src, weight_type{0}, M_g[src].size()-1);
    } else if (std::is_same<Directedness, undirected_tag>::value) {
      M_g[dst].emplace_back(dst, src, cap, M_g[src].size()-1);
    }
  }

  size_type size() const { return M_g.size(); }
  auto const& operator [](size_type i) const { return M_g[i]; }
  auto& operator [](size_type i) { return M_g[i]; }
};


#line 1 "Graph/dinitz.cpp"



/**
 * @brief 最大流 (Dinitz 法)
 * @author えびちゃん
 */

#include <queue>
#line 11 "Graph/dinitz.cpp"

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


#line 1 "utility/limits.cpp"



/**
 * @brief 型依存の定数
 * @author えびちゃん
 */

#include <limits>

template <typename Tp>
class limits: public std::numeric_limits<Tp> {};


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
#line 15 "Graph/dinitz.cpp"

struct dinitz_tag {} dinitz;

template <typename AdjacencyList>
auto max_flow(AdjacencyList& g, size_t s, size_t t,
              typename AdjacencyList::weight_type fl, dinitz_tag) {

  using size_type = typename AdjacencyList::size_type;
  using weight_type = typename AdjacencyList::weight_type;
  size_type n = g.size();
  std::vector<size_type> level(n), iter(n);

  auto bfs = [&](size_type s) -> void {
    level.assign(n, -1_zu);
    std::queue<size_type> q;
    level[s] = 0;
    q.push(s);
    while (!q.empty()) {
      size_type v = q.front();
      q.pop();
      for (auto const& e: g[v]) {
        if (e.capacity() > weight_type(0) && level[e.target()] == -1_zu) {
          level[e.target()] = level[e.source()] + 1;
          q.push(e.target());
        }
      }
    }
  };

  auto dfs = make_fix_point([&](auto dfs_, size_type v, weight_type f) -> weight_type {
      if (v == t) return f;
      for (size_type& i = iter[v]; i < g[v].size(); ++i) {
        auto& e = g[v][i];
        if (e.capacity() > weight_type(0) && level[v] < level[e.target()]) {
          weight_type f0 = dfs_(e.target(), std::min(f, e.capacity()));
          if (f0 > weight_type(0)) {
            e.capacity() -= f0;
            g[e.target()][e.reversed()].capacity() += f0;
            return f0;
          }
        }
      }
      return weight_type(0);
  });

  weight_type res{0};
  while (true) {
    bfs(s);
    if (level[t] == -1_zu) return res;
    iter.assign(n, 0);
    weight_type f;
    while ((f = dfs(s, fl)) > weight_type(0)) {
      res += f;
      fl -= f;
      if (fl == weight_type(0)) return res;
    }
  }
}

template <typename AdjacencyList>
auto max_flow(AdjacencyList& g, size_t s, size_t t, dinitz_tag) {
  auto fl = limits<typename AdjacencyList::weight_type>::max();
  return max_flow(g, s, t, fl, dinitz);
}


#line 8 "test/yj_bipartitematching.test.cpp"

int main() {
  size_t l, r, m;
  scanf("%zu %zu %zu", &l, &r, &m);

  adjacency_list<capacitated_edge<int>, directed_tag> g(l+r+2);
  size_t source = l+r;
  size_t sink = source+1;
  for (size_t i = 0; i < m; ++i) {
    size_t a, b;
    scanf("%zu %zu", &a, &b);
    g.emplace(a, l+b, 1);
  }

  for (size_t i = 0; i < l; ++i) g.emplace(source, i, 1);
  for (size_t i = 0; i < r; ++i) g.emplace(l+i, sink, 1);

  printf("%d\n", max_flow(g, source, sink, dinitz));

  for (size_t i = 0; i < l; ++i) {
    for (auto const& e: g[i]) {
      size_t j = e.target();
      if (j == source) continue;
      if (e.capacity() == 0) printf("%zu %zu\n", i, j-l);
    }
  }
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

