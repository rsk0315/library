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


# :heavy_check_mark: オンライン・オフライン変換 <small>(algorithm/online_to_offline_optimization.cpp)</small>

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#ed469618898d75b149e5c7c4b6a1c415">algorithm</a>
* <a href="{{ site.github.repository_url }}/blob/master/algorithm/online_to_offline_optimization.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-16 00:23:53+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/test/yc_703_onoff.test.cpp.html">test/yc_703_onoff.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yc_704_onoff.test.cpp.html">test/yc_704_onoff.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yc_705_onoff.test.cpp.html">test/yc_705_onoff.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
/**
 * @brief オンライン・オフライン変換
 * @author えびちゃん
 */

#ifndef H_online_to_offline_optimization
#define H_online_to_offline_optimization

#include <cstddef>
#include <algorithm>
#include <vector>

#ifdef CALL_FROM_TEST
#include "algorithm/monotone_minima.cpp"
#include "utility/limits.cpp"
#include "utility/make/fix_point.cpp"
#endif

template <typename Fn>
auto online_to_offline_optimization(Fn&& f, size_t n, decltype(f(n, n)) init = 0) {
  using value_type = decltype(f(n, n));
  std::vector<value_type> dp(n, limits<value_type>::max());
  dp[0] = init;

  auto induce = [&](size_t l, size_t m, size_t r) -> void {
    auto g = [&](size_t i, size_t j) -> value_type {
      return dp[j+l] + f(j+l, i+m);
    };
    auto argmin = monotone_minima(g, r-m, m-l);
    for (size_t i = m; i < r; ++i) {
      size_t j = argmin[i-m] + l;
      dp[i] = std::min(dp[i], g(i-m, j-l));
    }
  };

  make_fix_point([&](auto& solve, size_t l, size_t r) -> void {
      if (l+1 == r) {
        if (r < n) dp[r] = std::min(dp[r], dp[l] + f(l, r));
        return;
      }
      size_t m = (l+r) >> 1;
      solve(l, m);
      induce(l, m, r);
      solve(m, r);
  })(0, n);
  return dp;
}

#endif  /* !defined(H_online_to_offline_optimization) */

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
Traceback (most recent call last):
  File "/opt/hostedtoolcache/Python/3.8.2/x64/lib/python3.8/site-packages/onlinejudge_verify/docs.py", line 340, in write_contents
    bundled_code = language.bundle(self.file_class.file_path, basedir=pathlib.Path.cwd())
  File "/opt/hostedtoolcache/Python/3.8.2/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus.py", line 68, in bundle
    bundler.update(path)
  File "/opt/hostedtoolcache/Python/3.8.2/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py", line 281, in update
    raise BundleError(path, i + 1, "unable to process #include in #if / #ifdef / #ifndef other than include guards")
onlinejudge_verify.languages.cplusplus_bundle.BundleError: algorithm/online_to_offline_optimization.cpp: line 14: unable to process #include in #if / #ifdef / #ifndef other than include guards

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

