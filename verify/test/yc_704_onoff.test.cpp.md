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


# :heavy_check_mark: test/yc_704_onoff.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/yc_704_onoff.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-17 12:18:22+09:00


* see: <a href="https://yukicoder.me/problems/no/704">https://yukicoder.me/problems/no/704</a>


## Depends on

* :heavy_check_mark: <a href="../../library/algorithm/monotone_minima.cpp.html">monotone minima <small>(algorithm/monotone_minima.cpp)</small></a>
* :heavy_check_mark: <a href="../../library/algorithm/online_to_offline_optimization.cpp.html">オンライン・オフライン変換 <small>(algorithm/online_to_offline_optimization.cpp)</small></a>
* :heavy_check_mark: <a href="../../library/utility/limits.cpp.html">型依存の定数 <small>(utility/limits.cpp)</small></a>
* :heavy_check_mark: <a href="../../library/utility/make/fix_point.cpp.html">ラムダ式の再帰 <small>(utility/make/fix_point.cpp)</small></a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://yukicoder.me/problems/no/704"

#define CALL_FROM_TEST
#include "algorithm/online_to_offline_optimization.cpp"
#undef CALL_FROM_TEST

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>

int main() {
  size_t n;
  scanf("%zu", &n);

  std::vector<int> a(n), x(n), y(n);
  for (auto& ai: a) scanf("%d", &ai);
  for (auto& xi: x) scanf("%d", &xi);
  for (auto& yi: y) scanf("%d", &yi);

  auto f = [&](size_t j, size_t i) {
    intmax_t dx = x[j] - a[i-1];
    intmax_t dy = y[j];
    return std::abs(dx) + std::abs(dy);
  };

  auto dp = online_to_offline_optimization(f, n+1);
  printf("%jd\n", dp[n]);
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
onlinejudge_verify.languages.cplusplus_bundle.BundleError: algorithm/online_to_offline_optimization.cpp: line 14: unable to process #include in #if / #ifdef / #ifndef other than include guards

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

