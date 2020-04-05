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


# :heavy_check_mark: 補間多項式 <small>(ModularArithmetic/interpolation.cpp)</small>

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#495e431c85de4c533fce4ff12db613fe">ModularArithmetic</a>
* <a href="{{ site.github.repository_url }}/blob/master/ModularArithmetic/interpolation.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-04 20:25:55+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/test/yj_polynomial_interpolation.test.cpp.html">test/yj_polynomial_interpolation.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
/**
 * @brief 補間多項式
 * @author えびちゃん
 */

#ifndef H_interpolation
#define H_interpolation

#ifdef CALL_FROM_TEST
#include "ModularArithmetic/polynomial.cpp"
#include "integer/bit.cpp"
#endif

#include <cstddef>
#include <vector>

template <typename ModInt>
polynomial<ModInt> interpolate(std::vector<ModInt> const& xs, std::vector<ModInt> const& ys) {
  size_t n = xs.size();
  size_t n2 = ceil2(n);
  std::vector<polynomial<ModInt>> mul(n2+n2, {1}), g(n2+n2);
  for (size_t i = 0; i < n; ++i) mul[n2+i] = {-xs[i], 1};
  for (size_t i = n2; i-- > 1;) mul[i] = mul[i<<1|0] * mul[i<<1|1];

  auto f = mul[1];
  f.differentiate();

  g[1] = f % mul[1];
  for (size_t i = 2; i < n2+n; ++i) g[i] = g[i>>1] % mul[i];
  for (size_t i = 0; i < n; ++i) g[n2+i] = {ys[i] / g[n2+i][0]};
  for (size_t i = n2; i--;) g[i] = g[i<<1|0] * mul[i<<1|1] + g[i<<1|1] * mul[i<<1|0];
  return g[1];
}

#endif  /* !defined(H_interpolation) */

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
onlinejudge_verify.languages.cplusplus_bundle.BundleError: ModularArithmetic/interpolation.cpp: line 10: unable to process #include in #if / #ifdef / #ifndef other than include guards

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

