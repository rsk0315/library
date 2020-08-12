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


# :heavy_check_mark: 黄金比分割の三分探索 <small>(algorithm/ternary_search.cpp)</small>

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#ed469618898d75b149e5c7c4b6a1c415">algorithm</a>
* <a href="{{ site.github.repository_url }}/blob/master/algorithm/ternary_search.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-29 14:28:04+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/test/yc_306.test.cpp.html">test/yc_306.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yc_306_maximize.test.cpp.html">test/yc_306_maximize.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#ifndef H_ternary_search
#define H_ternary_search

/**
 * @brief 黄金比分割の三分探索
 * @author えびちゃん
 */

#include <cmath>
#include <utility>

template <typename Fn, typename Tp>
auto optimize_convex(Fn&& f, Tp xl, Tp xu, Tp err, bool maximize = true) {
  // Return {argmax f(x), max f(x)} if maximize, {argmin f(x), min f(x)}
  // otherwise.  If f is not convex in [xl, xu], the behavior is undefined.
  Tp const phi = (1 + std::sqrt(static_cast<Tp>(5))) / 2;
  int const iter = (std::log(xu-xl) - std::log(err)) / std::log(phi) + 1;
  Tp xml = (phi * xl + xu) / (1 + phi);
  Tp xmu = (xl + phi * xu) / (1 + phi);
  Tp yml = f(xml);
  Tp ymu = f(xmu);
  for (int i = 0; i < iter; ++i) {
    if (!maximize ^ (yml > ymu)) {
      xu = xmu;
      xmu = xml;
      ymu = yml;
      xml = (phi * xl + xu) / (1 + phi);
      yml = f(xml);
    } else {
      xl = xml;
      xml = xmu;
      yml = ymu;
      xmu = (xl + phi * xu) / (1 + phi);
      ymu = f(xmu);
    }
  }
  return std::make_pair(xml, yml);
}

#endif  /* !defined(H_ternary_search) */

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "algorithm/ternary_search.cpp"



/**
 * @brief 黄金比分割の三分探索
 * @author えびちゃん
 */

#include <cmath>
#include <utility>

template <typename Fn, typename Tp>
auto optimize_convex(Fn&& f, Tp xl, Tp xu, Tp err, bool maximize = true) {
  // Return {argmax f(x), max f(x)} if maximize, {argmin f(x), min f(x)}
  // otherwise.  If f is not convex in [xl, xu], the behavior is undefined.
  Tp const phi = (1 + std::sqrt(static_cast<Tp>(5))) / 2;
  int const iter = (std::log(xu-xl) - std::log(err)) / std::log(phi) + 1;
  Tp xml = (phi * xl + xu) / (1 + phi);
  Tp xmu = (xl + phi * xu) / (1 + phi);
  Tp yml = f(xml);
  Tp ymu = f(xmu);
  for (int i = 0; i < iter; ++i) {
    if (!maximize ^ (yml > ymu)) {
      xu = xmu;
      xmu = xml;
      ymu = yml;
      xml = (phi * xl + xu) / (1 + phi);
      yml = f(xml);
    } else {
      xl = xml;
      xml = xmu;
      yml = ymu;
      xmu = (xl + phi * xu) / (1 + phi);
      ymu = f(xmu);
    }
  }
  return std::make_pair(xml, yml);
}



```
{% endraw %}

<a href="../../index.html">Back to top page</a>

