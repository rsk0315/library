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


# :warning: 4-近傍 <small>(utility/four_neighbor.cpp)</small>

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#67b732dc42aaffa9056d34cc477c863c">utility</a>
* <a href="{{ site.github.repository_url }}/blob/master/utility/four_neighbor.cpp">View this file on GitHub</a>
    - Last commit date: 2020-07-11 14:53:01+09:00




## Depends on

* :question: <a href="literals.cpp.html">ユーザ定義リテラル <small>(utility/literals.cpp)</small></a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#ifndef H_four_neighbor
#define H_four_neighbor

/**
 * @brief 4-近傍
 * @author えびちゃん
 */

#include <cstddef>
#include <array>
#include <utility>

#include "utility/literals.cpp"

constexpr std::array<std::pair<size_t, size_t>, 4> dij4{
  {{-1_zu, 0}, {0, -1_zu}, {1, 0}, {0, 1}}
};

#endif  /* !defined(H_four_neighbor) */

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "utility/four_neighbor.cpp"



/**
 * @brief 4-近傍
 * @author えびちゃん
 */

#include <cstddef>
#include <array>
#include <utility>

#line 1 "utility/literals.cpp"



/**
 * @brief ユーザ定義リテラル
 * @author えびちゃん
 */

#line 10 "utility/literals.cpp"
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


#line 14 "utility/four_neighbor.cpp"

constexpr std::array<std::pair<size_t, size_t>, 4> dij4{
  {{-1_zu, 0}, {0, -1_zu}, {1, 0}, {0, 1}}
};



```
{% endraw %}

<a href="../../index.html">Back to top page</a>

