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
<script type="text/javascript" src="../../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../../assets/css/copy-button.css" />


# :heavy_check_mark: test/mini/qq.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#9a6d2aa7b36e38045ca314a0baa2d4bd">test/mini</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/mini/qq.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-23 22:46:40+09:00




## Verified with

* :heavy_check_mark: <a href="../../../verify/test/mini/fused_operations.test.cpp.html">test/mini/fused_operations.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#ifndef H_qq
#define H_qq

#include <cstdio>

void qq() {
  for (int i = 1; i <= 9; ++i)
    for (int j = 1; j <= 9; ++j)
      printf("%dx%d=%d\n", i, j, i*j);
}

#endif  /* !defined(H_qq) */

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/mini/qq.cpp"



#include <cstdio>

void qq() {
  for (int i = 1; i <= 9; ++i)
    for (int j = 1; j <= 9; ++j)
      printf("%dx%d=%d\n", i, j, i*j);
}



```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

