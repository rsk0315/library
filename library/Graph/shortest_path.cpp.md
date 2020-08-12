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


# :warning: グラフ上の最短距離 <small>(Graph/shortest_path.cpp)</small>

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#4cdbd2bafa8193091ba09509cedf94fd">Graph</a>
* <a href="{{ site.github.repository_url }}/blob/master/Graph/shortest_path.cpp">View this file on GitHub</a>
    - Last commit date: 1970-01-01 00:00:00+00:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#ifndef H_shortest_path
#define H_shortest_path

/**
 * @brief グラフ上の最短距離
 * @author えびちゃん
 */

#include <deque>
#include <functional>
#include <queue>
#include <utility>
#include <vector>

#include "utility/limits.cpp"

struct dijkstra_tag {} dijkstra;
struct bfs01_tag {} bfs01;

template <typename AdjacencyList>
auto shortest_path(AdjacencyList const& g, size_t s, dijkstra_tag) {
  size_t n = g.size();
  using weight_type = typename AdjacencyList::weight_type;
  using pair = std::pair<weight_type, size_t>;
  std::vector<weight_type> d(n, limits<weight_type>::max());
  d[s] = 0;
  std::priority_queue<pair, std::vector<pair>, std::greater<>> pq;
  pq.emplace(0, s);
  while (!pq.empty()) {
    auto [w, v] = pq.top();
    pq.pop();
    if (d[v] < w) continue;
    for (auto const& e: g[v]) {
      size_t nv = e.target();
      if (auto nw = w + e.weight(); nw < d[nv]) {
        d[nv] = nw;
        pq.emplace(nw, nv);
      }
    }
  }
  return d;
}

template <typename AdjacencyList>
auto shortest_path(AdjacencyList const& g, size_t s, bfs01_tag) {
  size_t n = g.size();
  std::vector<size_t> d(n, n);
  d[s] = 0;
  std::deque<size_t> dq;
  dq.push_back(s);
  while (!dq.empty()) {
    size_t v = dq.front();
    dq.pop_front();
    for (auto const& e: g[v]) {
      size_t nv = e.target();
      size_t nw = d[v] + ((e.weight() == 0)? 0: 1);
      if (!(nw < d[nv])) continue;
      d[nv] = nw;
      if (e.weight() == 0) {
        dq.push_front(nv);
      } else {
        dq.push_back(nv);
      }
    }
  }
  return d;
}

#endif  /* !defined(H_shortest_path) */

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "Graph/shortest_path.cpp"



/**
 * @brief グラフ上の最短距離
 * @author えびちゃん
 */

#include <deque>
#include <functional>
#include <queue>
#include <utility>
#include <vector>

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


#line 16 "Graph/shortest_path.cpp"

struct dijkstra_tag {} dijkstra;
struct bfs01_tag {} bfs01;

template <typename AdjacencyList>
auto shortest_path(AdjacencyList const& g, size_t s, dijkstra_tag) {
  size_t n = g.size();
  using weight_type = typename AdjacencyList::weight_type;
  using pair = std::pair<weight_type, size_t>;
  std::vector<weight_type> d(n, limits<weight_type>::max());
  d[s] = 0;
  std::priority_queue<pair, std::vector<pair>, std::greater<>> pq;
  pq.emplace(0, s);
  while (!pq.empty()) {
    auto [w, v] = pq.top();
    pq.pop();
    if (d[v] < w) continue;
    for (auto const& e: g[v]) {
      size_t nv = e.target();
      if (auto nw = w + e.weight(); nw < d[nv]) {
        d[nv] = nw;
        pq.emplace(nw, nv);
      }
    }
  }
  return d;
}

template <typename AdjacencyList>
auto shortest_path(AdjacencyList const& g, size_t s, bfs01_tag) {
  size_t n = g.size();
  std::vector<size_t> d(n, n);
  d[s] = 0;
  std::deque<size_t> dq;
  dq.push_back(s);
  while (!dq.empty()) {
    size_t v = dq.front();
    dq.pop_front();
    for (auto const& e: g[v]) {
      size_t nv = e.target();
      size_t nw = d[v] + ((e.weight() == 0)? 0: 1);
      if (!(nw < d[nv])) continue;
      d[nv] = nw;
      if (e.weight() == 0) {
        dq.push_front(nv);
      } else {
        dq.push_back(nv);
      }
    }
  }
  return d;
}



```
{% endraw %}

<a href="../../index.html">Back to top page</a>

