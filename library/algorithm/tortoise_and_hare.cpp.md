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


# :warning: 周期検出 <small>(algorithm/tortoise_and_hare.cpp)</small>

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#ed469618898d75b149e5c7c4b6a1c415">algorithm</a>
* <a href="{{ site.github.repository_url }}/blob/master/algorithm/tortoise_and_hare.cpp">View this file on GitHub</a>
    - Last commit date: 1970-01-01 00:00:00+00:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#ifndef H_tortoise_and_hare
#define H_tortoise_and_hare

/**
 * @brief 周期検出
 * @author えびちゃん
 */

#include <cstdint>
#include <utility>

template <typename Generator>
std::pair<intmax_t, intmax_t> detect_cycle(Generator g) {
  Generator tortoise = g;
  Generator hare = g;
  do {
    tortoise.pop();
    hare.pop(), hare.pop();
  } while (tortoise.peek() != hare.peek());

  tortoise = g;
  intmax_t mu = 0;
  while (tortoise.peek() != hare.peek()) {
    ++mu;
    tortoise.pop();
    hare.pop();
  }

  intmax_t lambda = 0;
  hare = tortoise;
  do {
    ++lambda;
    hare.pop();
  } while (tortoise.peek() != hare.peek());

  return {mu, lambda};
}

#endif  /* !defined(H_tortoise_and_hare) */

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "algorithm/tortoise_and_hare.cpp"



/**
 * @brief 周期検出
 * @author えびちゃん
 */

#include <cstdint>
#include <utility>

template <typename Generator>
std::pair<intmax_t, intmax_t> detect_cycle(Generator g) {
  Generator tortoise = g;
  Generator hare = g;
  do {
    tortoise.pop();
    hare.pop(), hare.pop();
  } while (tortoise.peek() != hare.peek());

  tortoise = g;
  intmax_t mu = 0;
  while (tortoise.peek() != hare.peek()) {
    ++mu;
    tortoise.pop();
    hare.pop();
  }

  intmax_t lambda = 0;
  hare = tortoise;
  do {
    ++lambda;
    hare.pop();
  } while (tortoise.peek() != hare.peek());

  return {mu, lambda};
}



```
{% endraw %}

<a href="../../index.html">Back to top page</a>

