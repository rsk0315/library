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


# :heavy_check_mark: ユーザ定義リテラル <small>(utility/literals.cpp)</small>

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#67b732dc42aaffa9056d34cc477c863c">utility</a>
* <a href="{{ site.github.repository_url }}/blob/master/utility/literals.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-21 16:32:25+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/test/ALDS1_5_D.test.cpp.html">test/ALDS1_5_D.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/GRL_5_C_segment_tree.test.cpp.html">test/GRL_5_C_segment_tree.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/GRL_5_C_sparse_table.test.cpp.html">test/GRL_5_C_sparse_table.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/GRL_5_C_squaring.test.cpp.html">test/GRL_5_C_squaring.test.cpp</a>
* :x: <a href="../../verify/test/aoj_3110.test.cpp.html">test/aoj_3110.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
/**
 * @brief ユーザ定義リテラル
 * @author えびちゃん
 */

#ifndef H_int_literals
#define H_int_literals
#include <cstddef>
#include <cstdint>

constexpr intmax_t  operator ""_jd(unsigned long long n) { return n; }
constexpr uintmax_t operator ""_ju(unsigned long long n) { return n; }
constexpr size_t    operator ""_zu(unsigned long long n) { return n; }
constexpr ptrdiff_t operator ""_td(unsigned long long n) { return n; }

#endif  /* !defined(H_int_literals) */

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "utility/literals.cpp"
/**
 * @brief ユーザ定義リテラル
 * @author えびちゃん
 */

#ifndef H_int_literals
#define H_int_literals
#include <cstddef>
#include <cstdint>

constexpr intmax_t  operator ""_jd(unsigned long long n) { return n; }
constexpr uintmax_t operator ""_ju(unsigned long long n) { return n; }
constexpr size_t    operator ""_zu(unsigned long long n) { return n; }
constexpr ptrdiff_t operator ""_td(unsigned long long n) { return n; }

#endif  /* !defined(H_int_literals) */

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

