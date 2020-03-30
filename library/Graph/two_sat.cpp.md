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


# :question: 2-SAT <small>(Graph/two_sat.cpp)</small>

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#4cdbd2bafa8193091ba09509cedf94fd">Graph</a>
* <a href="{{ site.github.repository_url }}/blob/master/Graph/two_sat.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-07 05:02:13+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/test/aoj_2178.test.cpp.html">test/aoj_2178.test.cpp</a>
* :x: <a href="../../verify/test/aoj_2991.test.cpp.html">test/aoj_2991.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
/**
 * @brief 2-SAT
 * @author えびちゃん
 */

#ifndef H_two_sat
#define H_two_sat

#ifdef CALL_FROM_TEST
#include "Graph/adjacency_list.cpp"
#include "Graph/scc.cpp"
#endif

#include <cstddef>
#include <vector>

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
  two_sat(two_sat const&) = default;
  two_sat(two_sat&&) = default;

  two_sat(size_type n): M_n(n), M_g(n+n) {}

  two_sat& operator =(two_sat const&) = default;
  two_sat& operator =(two_sat&&) = default;

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
Traceback (most recent call last):
  File "/opt/hostedtoolcache/Python/3.8.2/x64/lib/python3.8/site-packages/onlinejudge_verify/docs.py", line 340, in write_contents
    bundled_code = language.bundle(self.file_class.file_path, basedir=pathlib.Path.cwd())
  File "/opt/hostedtoolcache/Python/3.8.2/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus.py", line 170, in bundle
    bundler.update(path)
  File "/opt/hostedtoolcache/Python/3.8.2/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py", line 281, in update
    raise BundleError(path, i + 1, "unable to process #include in #if / #ifdef / #ifndef other than include guards")
onlinejudge_verify.languages.cplusplus_bundle.BundleError: Graph/two_sat.cpp: line 10: unable to process #include in #if / #ifdef / #ifndef other than include guards

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

