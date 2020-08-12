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


# :heavy_check_mark: 合同演算の前計算テーブル <small>(ModularArithmetic/modtable.cpp)</small>

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#495e431c85de4c533fce4ff12db613fe">ModularArithmetic</a>
* <a href="{{ site.github.repository_url }}/blob/master/ModularArithmetic/modtable.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-06 04:52:14+09:00




## Required by

* :heavy_check_mark: <a href="factorial.cpp.html">階乗の高速計算 <small>(ModularArithmetic/factorial.cpp)</small></a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/aoj_DPL_5_C.test.cpp.html">test/aoj_DPL_5_C.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj_DPL_5_D.test.cpp.html">test/aoj_DPL_5_D.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj_DPL_5_E.test.cpp.html">test/aoj_DPL_5_E.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj_DPL_5_F.test.cpp.html">test/aoj_DPL_5_F.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj_DPL_5_G.test.cpp.html">test/aoj_DPL_5_G.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj_DPL_5_I.test.cpp.html">test/aoj_DPL_5_I.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yc_502.test.cpp.html">test/yc_502.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#ifndef H_modtable
#define H_modtable

/**
 * @brief 合同演算の前計算テーブル
 * @author えびちゃん
 */

#include <cstddef>
#include <vector>

template <typename ModInt>
class modtable {
public:
  using value_type = ModInt;
  using size_type = size_t;
  using underlying_type = typename ModInt::value_type;

private:
  std::vector<value_type> M_f, M_i, M_fi;

public:
  modtable() = default;

  explicit modtable(underlying_type n): M_f(n+1), M_i(n+1), M_fi(n+1) {
    M_f[0] = 1;
    for (underlying_type i = 1; i <= n; ++i)
      M_f[i] = M_f[i-1] * i;

    underlying_type mod = M_f[0].get_modulo();
    M_i[1] = 1;
    for (underlying_type i = 2; i <= n; ++i)
      M_i[i] = -value_type(mod / i) * M_i[mod % i];

    M_fi[0] = 1;
    for (underlying_type i = 1; i <= n; ++i)
      M_fi[i] = M_fi[i-1] * M_i[i];
  }

  value_type inverse(underlying_type n) const { return M_i[n]; }
  value_type factorial(underlying_type n) const { return M_f[n]; }
  value_type factorial_inverse(underlying_type n) const { return M_fi[n]; }

  value_type binom(underlying_type n, underlying_type k) const {
    if (n < 0 || n < k || k < 0) return 0;
    // assumes n < mod
    return M_f[n] * M_fi[k] * M_fi[n-k];
  }
};

#endif  /* !defined(H_modtable) */

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "ModularArithmetic/modtable.cpp"



/**
 * @brief 合同演算の前計算テーブル
 * @author えびちゃん
 */

#include <cstddef>
#include <vector>

template <typename ModInt>
class modtable {
public:
  using value_type = ModInt;
  using size_type = size_t;
  using underlying_type = typename ModInt::value_type;

private:
  std::vector<value_type> M_f, M_i, M_fi;

public:
  modtable() = default;

  explicit modtable(underlying_type n): M_f(n+1), M_i(n+1), M_fi(n+1) {
    M_f[0] = 1;
    for (underlying_type i = 1; i <= n; ++i)
      M_f[i] = M_f[i-1] * i;

    underlying_type mod = M_f[0].get_modulo();
    M_i[1] = 1;
    for (underlying_type i = 2; i <= n; ++i)
      M_i[i] = -value_type(mod / i) * M_i[mod % i];

    M_fi[0] = 1;
    for (underlying_type i = 1; i <= n; ++i)
      M_fi[i] = M_fi[i-1] * M_i[i];
  }

  value_type inverse(underlying_type n) const { return M_i[n]; }
  value_type factorial(underlying_type n) const { return M_f[n]; }
  value_type factorial_inverse(underlying_type n) const { return M_fi[n]; }

  value_type binom(underlying_type n, underlying_type k) const {
    if (n < 0 || n < k || k < 0) return 0;
    // assumes n < mod
    return M_f[n] * M_fi[k] * M_fi[n-k];
  }
};



```
{% endraw %}

<a href="../../index.html">Back to top page</a>

