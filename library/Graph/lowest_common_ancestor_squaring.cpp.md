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


# :heavy_check_mark: 最深共通祖先 (squaring) <small>(Graph/lowest_common_ancestor_squaring.cpp)</small>

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#4cdbd2bafa8193091ba09509cedf94fd">Graph</a>
* <a href="{{ site.github.repository_url }}/blob/master/Graph/lowest_common_ancestor_squaring.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-21 16:32:25+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/test/aoj_GRL_5_C_squaring.test.cpp.html">test/aoj_GRL_5_C_squaring.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
/**
 * @brief 最深共通祖先 (squaring)
 * @author えびちゃん
 */

#ifndef H_lowest_common_ancestor_squaring
#define H_lowest_common_ancestor_squaring

#ifdef CALL_FROM_TEST
#include "utility/literals.cpp"
#endif

#include <cstddef>
#include <algorithm>
#include <tuple>
#include <utility>
#include <vector>

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

#endif  /* !defined(H_lowest_common_ancestor_squaring) */

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
onlinejudge_verify.languages.cplusplus_bundle.BundleError: Graph/lowest_common_ancestor_squaring.cpp: line 10: unable to process #include in #if / #ifdef / #ifndef other than include guards

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

