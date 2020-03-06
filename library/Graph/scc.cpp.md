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


# :x: 強連結成分分解 <small>(Graph/scc.cpp)</small>

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#4cdbd2bafa8193091ba09509cedf94fd">Graph</a>
* <a href="{{ site.github.repository_url }}/blob/master/Graph/scc.cpp">View this file on GitHub</a>
    - Last commit date: 2020-02-10 03:33:13+09:00




## Verified with

* :x: <a href="../../verify/test/aoj_2178.test.cpp.html">test/aoj_2178.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
/**
 * @brief 強連結成分分解
 * @author えびちゃん
 */

#ifndef H_strongly_connected_components
#define H_strongly_connected_components

#ifdef CALL_FROM_TEST
#include "utility/make/fix_point.cpp"
#include "Graph/adjacency_list.cpp"
#endif

#include <cstddef>
#include <vector>

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
  std::vector<unsigned> cmp(n);
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

#endif /* !defined(H_strongly_connected_components) */

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
Traceback (most recent call last):
  File "/opt/hostedtoolcache/Python/3.8.2/x64/lib/python3.8/site-packages/onlinejudge_verify/docs.py", line 347, in write_contents
    bundled_code = language.bundle(self.file_class.file_path, basedir=self.cpp_source_path)
  File "/opt/hostedtoolcache/Python/3.8.2/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus.py", line 68, in bundle
    bundler.update(path)
  File "/opt/hostedtoolcache/Python/3.8.2/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py", line 181, in update
    raise BundleError(path, i + 1, "unable to process #include in #if / #ifdef / #ifndef other than include guards")
onlinejudge_verify.languages.cplusplus_bundle.BundleError: Graph/scc.cpp: line 10: unable to process #include in #if / #ifdef / #ifndef other than include guards

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

