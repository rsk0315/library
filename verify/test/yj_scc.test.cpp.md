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


# :heavy_check_mark: test/yj_scc.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/yj_scc.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-04 05:05:06+09:00


* see: <a href="https://judge.yosupo.jp/problem/scc">https://judge.yosupo.jp/problem/scc</a>


## Depends on

* :heavy_check_mark: <a href="../../library/Graph/adjacency_list.cpp.html">重みつきグラフの隣接リスト <small>(Graph/adjacency_list.cpp)</small></a>
* :heavy_check_mark: <a href="../../library/Graph/scc.cpp.html">強連結成分分解 <small>(Graph/scc.cpp)</small></a>
* :heavy_check_mark: <a href="../../library/utility/make/fix_point.cpp.html">ラムダ式の再帰 <small>(utility/make/fix_point.cpp)</small></a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/scc"

#define CALL_FROM_TEST
#include "Graph/adjacency_list.cpp"
#include "Graph/scc.cpp"
#undef CALL_FROM_TEST

#include <cstddef>
#include <cstdio>
#include <algorithm>
#include <vector>

int main() {
  size_t n, m;
  scanf("%zu %zu", &n, &m);

  adjacency_list<weighted_edge<int>, directed_tag> g(n);
  for (size_t i = 0; i < m; ++i) {
    size_t u, v;
    scanf("%zu %zu", &u, &v);
    g.emplace(u, v, 1);
  }

  auto scc = strongly_connected_components(g);
  size_t k = *std::max_element(scc.begin(), scc.end()) + 1;

  std::vector<std::vector<size_t>> ts(k);
  for (size_t i = 0; i < n; ++i)
    ts[scc[i]].push_back(i);

  printf("%zu\n", k);
  for (size_t i = 0; i < k; ++i) {
    printf("%zu", ts[i].size());
    for (auto v: ts[i]) printf(" %zu", v);
    puts("");
  }
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
onlinejudge_verify.languages.cplusplus_bundle.BundleError: Graph/scc.cpp: line 10: unable to process #include in #if / #ifdef / #ifndef other than include guards

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

