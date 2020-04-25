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


# :heavy_check_mark: 最大流 (Dinitz 法) <small>(Graph/dinitz.cpp)</small>

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#4cdbd2bafa8193091ba09509cedf94fd">Graph</a>
* <a href="{{ site.github.repository_url }}/blob/master/Graph/dinitz.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-24 09:56:38+09:00




## Depends on

* :heavy_check_mark: <a href="../utility/limits.cpp.html">型依存の定数 <small>(utility/limits.cpp)</small></a>
* :heavy_check_mark: <a href="../utility/literals.cpp.html">ユーザ定義リテラル <small>(utility/literals.cpp)</small></a>
* :heavy_check_mark: <a href="../utility/make/fix_point.cpp.html">ラムダ式の再帰 <small>(utility/make/fix_point.cpp)</small></a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/aoj_2313.test.cpp.html">test/aoj_2313.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj_2976.test.cpp.html">test/aoj_2976.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yj_bipartitematching.test.cpp.html">test/yj_bipartitematching.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#ifndef H_max_flow_dinitz
#define H_max_flow_dinitz

/**
 * @brief 最大流 (Dinitz 法)
 * @author えびちゃん
 */

#include <queue>
#include <vector>

#include "utility/literals.cpp"
#include "utility/limits.cpp"
#include "utility/make/fix_point.cpp"

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

#endif  /* !defined(H_max_flow_dinitz) */

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "Graph/dinitz.cpp"



/**
 * @brief 最大流 (Dinitz 法)
 * @author えびちゃん
 */

#include <queue>
#include <vector>

#line 1 "utility/literals.cpp"



/**
 * @brief ユーザ定義リテラル
 * @author えびちゃん
 */

#include <cstddef>
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



```
{% endraw %}

<a href="../../index.html">Back to top page</a>

