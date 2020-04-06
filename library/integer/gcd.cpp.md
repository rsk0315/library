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


# :heavy_check_mark: 最大公約数 <small>(integer/gcd.cpp)</small>

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#157db7df530023575515d366c9b672e8">integer</a>
* <a href="{{ site.github.repository_url }}/blob/master/integer/gcd.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-06 23:03:06+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/test/aoj_2446.test.cpp.html">test/aoj_2446.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#ifndef H_gcd
#define H_gcd

/** 
 * @brief 最大公約数
 * @author えびちゃん
 */

#include <utility>

template <typename Tp>
Tp gcd(Tp m, Tp n) {
  while (n) std::swap(m %= n, n);
  return m;
}

#endif  /* !defined(H_gcd) */

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "integer/gcd.cpp"



/** 
 * @brief 最大公約数
 * @author えびちゃん
 */

#include <utility>

template <typename Tp>
Tp gcd(Tp m, Tp n) {
  while (n) std::swap(m %= n, n);
  return m;
}



```
{% endraw %}

<a href="../../index.html">Back to top page</a>

