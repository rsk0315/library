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


# :heavy_check_mark: test/aoj_GRL_5_E.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/aoj_GRL_5_E.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-04 02:52:37+09:00


* see: <a href="https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_E">https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_E</a>


## Depends on

* :heavy_check_mark: <a href="../../library/DataStructure/segment_tree.cpp.html">区間作用・区間和セグメント木 <small>(DataStructure/segment_tree.cpp)</small></a>
* :heavy_check_mark: <a href="../../library/Graph/hl_decomposition.cpp.html">HL 分解 <small>(Graph/hl_decomposition.cpp)</small></a>
* :heavy_check_mark: <a href="../../library/integer/bit.cpp.html">ビット演算 <small>(integer/bit.cpp)</small></a>
* :heavy_check_mark: <a href="../../library/utility/action/add_sum.cpp.html">区間和・区間加算用のヘルパークラス <small>(utility/action/add_sum.cpp)</small></a>
* :heavy_check_mark: <a href="../../library/utility/monoid/length.cpp.html">和と長さを得る演算のモノイド <small>(utility/monoid/length.cpp)</small></a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_E"

#define CALL_FROM_TEST
// #include "utility/stack_extend.cpp"
#include "utility/action/add_sum.cpp"
#include "DataStructure/segment_tree.cpp"
#include "Graph/hl_decomposition.cpp"
#undef CALL_FROM_TEST

#include <cstdint>
#include <cstdio>
#include <cassert>
#include <tuple>
#include <vector>

int main() {
  // BEGIN_STACK_EXTEND(256*1024*1024);

  size_t n;
  scanf("%zu", &n);

  std::vector<size_t> par(n, n);
  std::vector<std::tuple<size_t, size_t, length_monoid<intmax_t>>> es;
  for (size_t i = 0; i < n; ++i) {
    size_t k;
    scanf("%zu", &k);
    for (size_t j = 0; j < k; ++j) {
      size_t c;
      scanf("%zu", &c);
      par[c] = i;
      es.emplace_back(i, c, 0);
    }
  }

  hl_decomposed_tree<segment_tree<action_add_to_sum<intmax_t>>, value_on_undirected_edge_tag> g(n, es);

  size_t q;
  scanf("%zu", &q);

  for (size_t i = 0; i < q; ++i) {
    int t;
    scanf("%d", &t);

    if (t == 0) {
      size_t v;
      intmax_t w;
      scanf("%zu %jd", &v, &w);
      g.act(v, 0, w);
    } else if (t == 1) {
      size_t u;
      scanf("%zu", &u);
      intmax_t res = g.fold(u, 0).get();
      assert(res == g.fold(0, u).get());
      printf("%jd\n", res);
    }
  }

  // END_STACK_EXTEND;
}

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
  File "/opt/hostedtoolcache/Python/3.8.2/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py", line 282, in update
    self.update(self._resolve(pathlib.Path(included), included_from=path))
  File "/opt/hostedtoolcache/Python/3.8.2/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py", line 281, in update
    raise BundleError(path, i + 1, "unable to process #include in #if / #ifdef / #ifndef other than include guards")
onlinejudge_verify.languages.cplusplus_bundle.BundleError: utility/action/add_sum.cpp: line 10: unable to process #include in #if / #ifdef / #ifndef other than include guards

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

