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


# :heavy_check_mark: test/GRL_5_C_segment_tree.test.cpp

<a href="../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/test/GRL_5_C_segment_tree.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-02-01 04:11:17+09:00


* see: <a href="https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_C">https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_C</a>


## Depends on

* :heavy_check_mark: <a href="../../library/Graph/adjacency_list.cpp.html">重みつきグラフの隣接リスト <small>(Graph/adjacency_list.cpp)</small></a>
* :heavy_check_mark: <a href="../../library/Graph/lowest_common_ancestor_segment_tree.cpp.html">最深共通祖先 (segment tree) <small>(Graph/lowest_common_ancestor_segment_tree.cpp)</small></a>
* :heavy_check_mark: <a href="../../library/integer/bit.cpp.html">ビット演算 <small>(integer/bit.cpp)</small></a>
* :heavy_check_mark: <a href="../../library/utility/literals.cpp.html">ユーザ定義リテラル <small>(utility/literals.cpp)</small></a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_C"

#define CALL_FROM_TEST
#include "Graph/adjacency_list.cpp"
#include "Graph/lowest_common_ancestor_segment_tree.cpp"
#undef CALL_FROM_TEST

#include <cstdint>
#include <cstdio>
#include <vector>

int main() {
  int n;
  scanf("%d", &n);

  adjacency_list<weighted_edge<int>, undirected_tag> g(n);
  for (size_t i = 0; i < n; ++i) {
    size_t k;
    scanf("%zu", &k);
    for (size_t j = 0; j < k; ++j) {
      size_t c;
      scanf("%zu", &c);
      g.emplace(i, c, 1);
    }
  }

  lowest_common_ancestor g_lca(g, 0);

  size_t q;
  scanf("%zu", &q);
  for (size_t i = 0; i < q; ++i) {
    size_t u, v;
    scanf("%zu %zu", &u, &v);
    printf("%zu\n", g_lca(u, v));
  }
}

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
  File "/opt/hostedtoolcache/Python/3.8.1/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py", line 182, in update
    self.update(self._resolve(included, included_from=path))
  File "/opt/hostedtoolcache/Python/3.8.1/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py", line 181, in update
    raise BundleError(path, i + 1, "unable to process #include in #if / #ifdef / #ifndef other than include guards")
onlinejudge_verify.languages.cplusplus_bundle.BundleError: Graph/lowest_common_ancestor_segment_tree.cpp: line 10: unable to process #include in #if / #ifdef / #ifndef other than include guards

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

