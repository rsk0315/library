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


# :heavy_check_mark: 最大流 (Dinitz) <small>(Graph/dinitz.cpp)</small>

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#4cdbd2bafa8193091ba09509cedf94fd">Graph</a>
* <a href="{{ site.github.repository_url }}/blob/master/Graph/dinitz.cpp">View this file on GitHub</a>
    - Last commit date: 2020-02-09 19:15:55+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/test/aoj_2313.test.cpp.html">test/aoj_2313.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj_2976.test.cpp.html">test/aoj_2976.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
/**
 * @brief 最大流 (Dinitz)
 * @author えびちゃん
 */

#ifndef H_max_flow_dinitz
#define H_max_flow_dinitz

#ifdef CALL_FROM_TEST
#include "utility/literals.cpp"
#include "utility/limits.cpp"
#include "utility/make/fix_point.cpp"
#include "Graph/adjacency_list.cpp"
#include "Graph/capacitated_list.cpp"
#endif

#include <queue>
#include <vector>

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
Traceback (most recent call last):
  File "/opt/hostedtoolcache/Python/3.8.1/x64/lib/python3.8/site-packages/onlinejudge_verify/docs.py", line 348, in write_contents
    bundled_code = language.bundle(self.file_class.file_path, basedir=self.cpp_source_path)
  File "/opt/hostedtoolcache/Python/3.8.1/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus.py", line 63, in bundle
    bundler.update(path)
  File "/opt/hostedtoolcache/Python/3.8.1/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py", line 181, in update
    raise BundleError(path, i + 1, "unable to process #include in #if / #ifdef / #ifndef other than include guards")
onlinejudge_verify.languages.cplusplus_bundle.BundleError: Graph/dinitz.cpp: line 10: unable to process #include in #if / #ifdef / #ifndef other than include guards

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

