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


# :warning: 素因数分解 <small>(Math/factor.cpp)</small>

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#a49950aa047c2292e989e368a97a3aae">Math</a>
* <a href="{{ site.github.repository_url }}/blob/master/Math/factor.cpp">View this file on GitHub</a>
    - Last commit date: 1970-01-01 00:00:00+00:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#ifndef H_factor
#define H_factor

/**
 * @brief 素因数分解
 * @author えびちゃん
 */

#include <cstdint>
#include <map>

std::map<intmax_t, int> factor(intmax_t n) {
  std::map<intmax_t, int> res;
  for (intmax_t i = 2; i*i <= n; ++i) {
    if (n % i != 0) continue;
    do {
      ++res[i];
      n /= i;
    } while (n % i == 0);
  }
  if (n > 1) ++res[n];
  return res;
}

#endif  /* !defined(H_factor) */

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "Math/factor.cpp"



/**
 * @brief 素因数分解
 * @author えびちゃん
 */

#include <cstdint>
#include <map>

std::map<intmax_t, int> factor(intmax_t n) {
  std::map<intmax_t, int> res;
  for (intmax_t i = 2; i*i <= n; ++i) {
    if (n % i != 0) continue;
    do {
      ++res[i];
      n /= i;
    } while (n % i == 0);
  }
  if (n > 1) ++res[n];
  return res;
}



```
{% endraw %}

<a href="../../index.html">Back to top page</a>

