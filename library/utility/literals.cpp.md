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


# :warning: ユーザ定義リテラル <small>(utility/literals.cpp)</small>

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#67b732dc42aaffa9056d34cc477c863c">utility</a>
* <a href="{{ site.github.repository_url }}/blob/master/utility/literals.cpp">View this file on GitHub</a>
    - Last commit date: 1970-01-01 00:00:00+00:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#ifndef H_int_literals
#define H_int_literals

/**
 * @brief ユーザ定義リテラル
 * @author えびちゃん
 */

#include <cstddef>
#include <cstdint>

constexpr intmax_t  operator ""_jd(unsigned long long n) { return n; }
constexpr uintmax_t operator ""_ju(unsigned long long n) { return n; }
constexpr size_t    operator ""_zu(unsigned long long n) { return n; }
constexpr ptrdiff_t operator ""_td(unsigned long long n) { return n; }

constexpr int8_t   operator ""_i8(unsigned long long n)  { return n; }
constexpr int16_t  operator ""_i16(unsigned long long n) { return n; }
constexpr int32_t  operator ""_i32(unsigned long long n) { return n; }
constexpr int64_t  operator ""_i64(unsigned long long n) { return n; }
constexpr uint8_t  operator ""_u8(unsigned long long n)  { return n; }
constexpr uint16_t operator ""_u16(unsigned long long n) { return n; }
constexpr uint32_t operator ""_u32(unsigned long long n) { return n; }
constexpr uint64_t operator ""_u64(unsigned long long n) { return n; }

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

#include <cstddef>
#include <cstdint>

constexpr intmax_t  operator ""_jd(unsigned long long n) { return n; }
constexpr uintmax_t operator ""_ju(unsigned long long n) { return n; }
constexpr size_t    operator ""_zu(unsigned long long n) { return n; }
constexpr ptrdiff_t operator ""_td(unsigned long long n) { return n; }

constexpr int8_t   operator ""_i8(unsigned long long n)  { return n; }
constexpr int16_t  operator ""_i16(unsigned long long n) { return n; }
constexpr int32_t  operator ""_i32(unsigned long long n) { return n; }
constexpr int64_t  operator ""_i64(unsigned long long n) { return n; }
constexpr uint8_t  operator ""_u8(unsigned long long n)  { return n; }
constexpr uint16_t operator ""_u16(unsigned long long n) { return n; }
constexpr uint32_t operator ""_u32(unsigned long long n) { return n; }
constexpr uint64_t operator ""_u64(unsigned long long n) { return n; }



```
{% endraw %}

<a href="../../index.html">Back to top page</a>

