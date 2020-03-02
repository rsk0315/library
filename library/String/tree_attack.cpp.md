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


# :heavy_check_mark: tree attack <small>(String/tree_attack.cpp)</small>

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#27118326006d3829667a400ad23d5d98">String</a>
* <a href="{{ site.github.repository_url }}/blob/master/String/tree_attack.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-03 04:19:38+09:00


* see: <a href="https://codeforces.com/blog/entry/60442">https://codeforces.com/blog/entry/60442</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/yc_3014.test.cpp.html">test/yc_3014.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
/**
 * @brief tree attack
 * @author えびちゃん
 * @see https://codeforces.com/blog/entry/60442
 */

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <queue>
#include <tuple>
#include <vector>

#ifdef CALL_FROM_TEST
#include "utility/literals.cpp"
#endif

std::vector<int> tree_attack(intmax_t p, intmax_t b, size_t k) {
  struct node {
    intmax_t value;
    size_t pos, neg;
    node() = default;
    node(intmax_t v, size_t l, size_t r): value(v), pos(l), neg(r) {}
    bool operator <(node const& that) const { return value < that.value; }
  };

  std::vector<std::vector<node>> cl(k+1);
  size_t n = 1_zu << k;
  cl[0].assign(n, node(1, n-1, -1_zu));
  for (size_t j = 1; j < n; ++j) {
    cl[0][j].value = __int128(cl[0][j-1].value) * b % p;
    cl[0][j].pos = n-1-j;
  }
  std::sort(cl[0].begin(), cl[0].end());

  for (size_t i = 1; i <= k; ++i) {
    cl[i].resize(n >> i);
    for (size_t j = 0; j < cl[i].size(); ++j) {
      size_t jl = j << 1 | 0;
      size_t jr = j << 1 | 1;
      if (cl[i-1][jr] < cl[i-1][jl]) {
        cl[i][j].value = cl[i-1][jl].value - cl[i-1][jr].value;
        cl[i][j].pos = jl;
        cl[i][j].neg = jr;
      } else {
        cl[i][j].value = cl[i-1][jr].value - cl[i-1][jl].value;
        cl[i][j].pos = jr;
        cl[i][j].neg = jl;
      }
    }
    std::sort(cl[i].begin(), cl[i].end());
    if (cl[i][0].value > 0) continue;

    std::vector<int> res(n, 0);
    std::queue<std::tuple<size_t, size_t, bool>> q;  // i, j, neg?
    q.emplace(i-1, cl[i][0].pos, false);
    q.emplace(i-1, cl[i][0].neg, true);
    while (!q.empty()) {
      auto [i, j, neg] = q.front();
      q.pop();
      if (i == -1_zu) {
        if (j != -1_zu) res[j] = (neg? -1: +1);
        continue;
      }
      q.emplace(i-1, cl[i][j].pos, neg);
      q.emplace(i-1, cl[i][j].neg, !neg);
    }
    return res;
  }
  return {};
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
Traceback (most recent call last):
  File "/opt/hostedtoolcache/Python/3.8.1/x64/lib/python3.8/site-packages/onlinejudge_verify/docs.py", line 347, in write_contents
    bundled_code = language.bundle(self.file_class.file_path, basedir=self.cpp_source_path)
  File "/opt/hostedtoolcache/Python/3.8.1/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus.py", line 68, in bundle
    bundler.update(path)
  File "/opt/hostedtoolcache/Python/3.8.1/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py", line 181, in update
    raise BundleError(path, i + 1, "unable to process #include in #if / #ifdef / #ifndef other than include guards")
onlinejudge_verify.languages.cplusplus_bundle.BundleError: String/tree_attack.cpp: line 15: unable to process #include in #if / #ifdef / #ifndef other than include guards

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

