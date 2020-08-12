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


# :heavy_check_mark: 整数の平方根 <small>(integer/sqrt.cpp)</small>

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#157db7df530023575515d366c9b672e8">integer</a>
* <a href="{{ site.github.repository_url }}/blob/master/integer/sqrt.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-06 23:03:06+09:00




## Required by

* :heavy_check_mark: <a href="../ModularArithmetic/factorial.cpp.html">階乗の高速計算 <small>(ModularArithmetic/factorial.cpp)</small></a>
* :heavy_check_mark: <a href="../algorithm/mo.cpp.html">Mo's algorithm <small>(algorithm/mo.cpp)</small></a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/aoj_0425.test.cpp.html">test/aoj_0425.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yc_502.test.cpp.html">test/yc_502.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#ifndef H_int_sqrt
#define H_int_sqrt

/**
 * @brief 整数の平方根
 * @author えびちゃん
 */

#include <climits>

template <typename Tp>
Tp isqrt(Tp n) {
  if (n <= 1) return n;
  Tp lb = 1;
  Tp ub = static_cast<Tp>(1) << (CHAR_BIT * (sizeof(Tp) / 2));
  while (ub-lb > 1) {
    Tp mid = (lb+ub) >> 1;
    ((mid*mid <= n)? lb: ub) = mid;
  }
  return lb;
}

#endif  /* !defined(H_int_sqrt) */

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "integer/sqrt.cpp"



/**
 * @brief 整数の平方根
 * @author えびちゃん
 */

#include <climits>

template <typename Tp>
Tp isqrt(Tp n) {
  if (n <= 1) return n;
  Tp lb = 1;
  Tp ub = static_cast<Tp>(1) << (CHAR_BIT * (sizeof(Tp) / 2));
  while (ub-lb > 1) {
    Tp mid = (lb+ub) >> 1;
    ((mid*mid <= n)? lb: ub) = mid;
  }
  return lb;
}



```
{% endraw %}

<a href="../../index.html">Back to top page</a>

