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


# :warning: 条件つき代入 <small>(utility/set_if.cpp)</small>

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#67b732dc42aaffa9056d34cc477c863c">utility</a>
* <a href="{{ site.github.repository_url }}/blob/master/utility/set_if.cpp">View this file on GitHub</a>
    - Last commit date: 2020-07-11 14:48:55+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#ifndef H_set_if
#define H_set_if

/**
 * @brief 条件つき代入
 * @author えびちゃん
 */

#include <algorithm>

template <typename Tp>
bool set_if_less(Tp& dst, Tp const& src) {
  if (src < dst) return (dst = src), true;
  return false;
}

template <typename Tp>
bool set_if_greater(Tp& dst, Tp const& src) {
  if (dst < src) return (dst = src), true;
  return false;
}

#endif  /* !defined(H_set_if) */

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "utility/set_if.cpp"



/**
 * @brief 条件つき代入
 * @author えびちゃん
 */

#include <algorithm>

template <typename Tp>
bool set_if_less(Tp& dst, Tp const& src) {
  if (src < dst) return (dst = src), true;
  return false;
}

template <typename Tp>
bool set_if_greater(Tp& dst, Tp const& src) {
  if (dst < src) return (dst = src), true;
  return false;
}



```
{% endraw %}

<a href="../../index.html">Back to top page</a>

