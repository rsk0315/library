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


# :heavy_check_mark: monotone minima <small>(algorithm/monotone_minima.cpp)</small>

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#ed469618898d75b149e5c7c4b6a1c415">algorithm</a>
* <a href="{{ site.github.repository_url }}/blob/master/algorithm/monotone_minima.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-16 00:23:53+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/test/aoj_2580.test.cpp.html">test/aoj_2580.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yc_703.test.cpp.html">test/yc_703.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
/**
 * @brief monotone minima
 * @author えびちゃん
 */

#ifndef H_monotone_minima
#define H_monotone_minima

#include <cstddef>
#include <utility>
#include <vector>

#ifdef CALL_FROM_TEST
#include "utility/make/fix_point.cpp"
#endif

template <typename Fn>
auto monotone_minima(Fn&& f, size_t h, size_t w) {
  using value_type = decltype(f(h, w));
  std::vector<size_t> res(h);

  make_fix_point([&](auto dfs, size_t hl, size_t hu, size_t wl, size_t wu) -> void {
      if (hl >= hu) return;
      size_t hm = (hl+hu) >> 1;
      value_type min = f(hm, wl);
      res[hm] = wl;
      for (size_t j = wl+1; j < wu; ++j) {
        value_type cur = f(hm, j);
        if (cur < min) {
          min = std::move(cur);
          res[hm] = j;
        }
      }
      if (hl == hm) return;
      dfs(hl, hm, wl, res[hm]+1);
      dfs(hm+1, hu, res[hm], wu);
  })(0, h, 0, w);
  return res;
}

#endif /* !defined(H_monotone_minima) */

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
onlinejudge_verify.languages.cplusplus_bundle.BundleError: algorithm/monotone_minima.cpp: line 14: unable to process #include in #if / #ifdef / #ifndef other than include guards

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

