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


# :x: トポロジカルソート <small>(Graph/topological_sort.cpp)</small>

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#4cdbd2bafa8193091ba09509cedf94fd">Graph</a>
* <a href="{{ site.github.repository_url }}/blob/master/Graph/topological_sort.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-31 04:28:00+09:00




## Verified with

* :x: <a href="../../verify/test/aoj_GRL_4_B.test.cpp.html">test/aoj_GRL_4_B.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
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

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
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

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

