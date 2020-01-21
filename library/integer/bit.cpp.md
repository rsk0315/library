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


# :heavy_check_mark: ビット演算 <small>(integer/bit.cpp)</small>

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#157db7df530023575515d366c9b672e8">integer</a>
* <a href="{{ site.github.repository_url }}/blob/master/integer/bit.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-21 16:32:25+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/test/GRL_5_C_segment_tree.test.cpp.html">test/GRL_5_C_segment_tree.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/GRL_5_C_sparse_table.test.cpp.html">test/GRL_5_C_sparse_table.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
/** 
 * @brief ビット演算
 * @author えびちゃん
 */

#ifndef H_bit
#define H_bit

template <typename Tp>
int ilog2(Tp n) {
  // - range_error を投げる？
  // - Tp は符号なしに限る？
  // - __has_builtin で分岐する？
  // - Tp のビット幅で分岐する？
  return 63 - __builtin_clzll(n);
}

#endif  /* !defined(H_bit) */

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "integer/bit.cpp"
/** 
 * @brief ビット演算
 * @author えびちゃん
 */

#ifndef H_bit
#define H_bit

template <typename Tp>
int ilog2(Tp n) {
  // - range_error を投げる？
  // - Tp は符号なしに限る？
  // - __has_builtin で分岐する？
  // - Tp のビット幅で分岐する？
  return 63 - __builtin_clzll(n);
}

#endif  /* !defined(H_bit) */

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

