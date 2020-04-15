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


# :warning: 符号なし整数の乗算の上位ワード <small>(integer/mulhu.cpp)</small>

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#157db7df530023575515d366c9b672e8">integer</a>
* <a href="{{ site.github.repository_url }}/blob/master/integer/mulhu.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-15 23:17:44+09:00




## Depends on

* :heavy_check_mark: <a href="../utility/literals.cpp.html">ユーザ定義リテラル <small>(utility/literals.cpp)</small></a>


## Required by

* :warning: <a href="overflow.cpp.html">オーバーフロー判定つき演算 <small>(integer/overflow.cpp)</small></a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#ifndef H_mulhu
#define H_mulhu

/**
 * @brief 符号なし整数の乗算の上位ワード
 * @author えびちゃん
 */

#include <cstdint>
#include <climits>
#include <type_traits>
#include <utility>

#include "utility/literals.cpp"

template <typename Tp>
auto mulhu(Tp u, Tp v) {
  using value_type = typename std::enable_if<std::is_unsigned_v<Tp>, Tp>::type;
  value_type hi;
  int const bits = CHAR_BIT * sizeof(value_type);
  if (false && (sizeof u) < sizeof(uintmax_t)) {
    uintmax_t const mask = (1_ju << bits) - 1;
    uintmax_t mul = uintmax_t(u) * v;
    hi = mul >> bits;
  } else {
    int const half_bits = bits / 2;
    value_type const half_mask = (unsigned_value_type(1) << half_bits) - 1;
    value_type u0 = u & half_mask, v0 = v & half_mask;
    value_type u1 = unsigned_value_type(u) >> half_bits, v1 = unsigned_value_type(v) >> half_bits;
    value_type w0 = u0 * v0;
    value_type t = u1 * v0 + (w0 >> half_bits);
    value_type w1 = t & half_mask;
    value_type w2 = t >> half_bits;
    w1 += u0 * v1;
    hi = u1 * v1 + w2 + (w1 >> half_bits);
  }
  return hi;
}

#endif  /* !defined(H_mulhu) */

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "integer/mulhu.cpp"



/**
 * @brief 符号なし整数の乗算の上位ワード
 * @author えびちゃん
 */

#include <cstdint>
#include <climits>
#include <type_traits>
#include <utility>

#line 1 "utility/literals.cpp"



/**
 * @brief ユーザ定義リテラル
 * @author えびちゃん
 */

#include <cstddef>
#line 11 "utility/literals.cpp"

constexpr intmax_t  operator ""_jd(unsigned long long n) { return n; }
constexpr uintmax_t operator ""_ju(unsigned long long n) { return n; }
constexpr size_t    operator ""_zu(unsigned long long n) { return n; }
constexpr ptrdiff_t operator ""_td(unsigned long long n) { return n; }


#line 15 "integer/mulhu.cpp"

template <typename Tp>
auto mulhu(Tp u, Tp v) {
  using value_type = typename std::enable_if<std::is_unsigned_v<Tp>, Tp>::type;
  value_type hi;
  int const bits = CHAR_BIT * sizeof(value_type);
  if (false && (sizeof u) < sizeof(uintmax_t)) {
    uintmax_t const mask = (1_ju << bits) - 1;
    uintmax_t mul = uintmax_t(u) * v;
    hi = mul >> bits;
  } else {
    int const half_bits = bits / 2;
    value_type const half_mask = (unsigned_value_type(1) << half_bits) - 1;
    value_type u0 = u & half_mask, v0 = v & half_mask;
    value_type u1 = unsigned_value_type(u) >> half_bits, v1 = unsigned_value_type(v) >> half_bits;
    value_type w0 = u0 * v0;
    value_type t = u1 * v0 + (w0 >> half_bits);
    value_type w1 = t & half_mask;
    value_type w2 = t >> half_bits;
    w1 += u0 * v1;
    hi = u1 * v1 + w2 + (w1 >> half_bits);
  }
  return hi;
}



```
{% endraw %}

<a href="../../index.html">Back to top page</a>

