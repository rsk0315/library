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


# :question: Garner's algorithm <small>(ModularArithmetic/garner.cpp)</small>

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#495e431c85de4c533fce4ff12db613fe">ModularArithmetic</a>
* <a href="{{ site.github.repository_url }}/blob/master/ModularArithmetic/garner.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-06 04:52:14+09:00




## Required by

* :x: <a href="factorial.cpp.html">階乗の高速計算 <small>(ModularArithmetic/factorial.cpp)</small></a>
* :heavy_check_mark: <a href="interpolation.cpp.html">補間多項式 <small>(ModularArithmetic/interpolation.cpp)</small></a>
* :question: <a href="polynomial.cpp.html">多項式 <small>(ModularArithmetic/polynomial.cpp)</small></a>


## Verified with

* :x: <a href="../../verify/test/yc_502.test.cpp.html">test/yc_502.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yj_convolution_mod.test.cpp.html">test/yj_convolution_mod.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yj_convolution_mod_1000000007.test.cpp.html">test/yj_convolution_mod_1000000007.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yj_inv_of_formal_power_series.test.cpp.html">test/yj_inv_of_formal_power_series.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yj_log_of_formal_power_series.test.cpp.html">test/yj_log_of_formal_power_series.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yj_multipoint_evaluation.test.cpp.html">test/yj_multipoint_evaluation.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yj_polynomial_interpolation.test.cpp.html">test/yj_polynomial_interpolation.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#ifndef H_garner
#define H_garner

/**
 * @brief Garner's algorithm
 * @author えびちゃん
 */

#include <algorithm>
#include <tuple>
#include <utility>

class simultaneous_congruences_garner {
public:
  using value_type = intmax_t;
  using size_type = size_t;

private:
  value_type M_mod = 1;
  value_type M_sol = 0;
  std::vector<value_type> M_c, M_m;

  static auto S_gcd_bezout(value_type a, value_type b) {
    value_type x{1}, y{0};
    for (value_type u{y}, v{x}; b != 0;) {
      value_type q{a/b};
      std::swap(x -= q*u, u);
      std::swap(y -= q*v, v);
      std::swap(a -= q*b, b);
    }
    return std::make_tuple(a, x, y);
  }

public:
  simultaneous_congruences_garner() = default;

  void push(value_type a, value_type m) {
    if (M_c.empty()) {
      M_c.push_back(a);
      M_m.push_back(m);
      return;
    }

    value_type c = M_c.back();
    value_type mi = M_m.back();
    for (size_type i = M_c.size()-1; i--;) {
      c = (c * M_m[i] + M_c[i]) % m;
      (mi *= M_m[i]) %= m;
    }
    c = (a-c) * std::get<1>(S_gcd_bezout(mi, m)) % m;
    if (c < 0) c += m;
    M_c.push_back(c);
    M_m.push_back(m);
  }

  auto get(value_type m) const {
    value_type x = M_c.back() % m;
    for (size_type i = M_c.size()-1; i--;) {
      x = (x * M_m[i] + M_c[i]) % m;
    }
    return x;
  }
};

#endif  /* !defined(H_garner) */

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "ModularArithmetic/garner.cpp"



/**
 * @brief Garner's algorithm
 * @author えびちゃん
 */

#include <algorithm>
#include <tuple>
#include <utility>

class simultaneous_congruences_garner {
public:
  using value_type = intmax_t;
  using size_type = size_t;

private:
  value_type M_mod = 1;
  value_type M_sol = 0;
  std::vector<value_type> M_c, M_m;

  static auto S_gcd_bezout(value_type a, value_type b) {
    value_type x{1}, y{0};
    for (value_type u{y}, v{x}; b != 0;) {
      value_type q{a/b};
      std::swap(x -= q*u, u);
      std::swap(y -= q*v, v);
      std::swap(a -= q*b, b);
    }
    return std::make_tuple(a, x, y);
  }

public:
  simultaneous_congruences_garner() = default;

  void push(value_type a, value_type m) {
    if (M_c.empty()) {
      M_c.push_back(a);
      M_m.push_back(m);
      return;
    }

    value_type c = M_c.back();
    value_type mi = M_m.back();
    for (size_type i = M_c.size()-1; i--;) {
      c = (c * M_m[i] + M_c[i]) % m;
      (mi *= M_m[i]) %= m;
    }
    c = (a-c) * std::get<1>(S_gcd_bezout(mi, m)) % m;
    if (c < 0) c += m;
    M_c.push_back(c);
    M_m.push_back(m);
  }

  auto get(value_type m) const {
    value_type x = M_c.back() % m;
    for (size_type i = M_c.size()-1; i--;) {
      x = (x * M_m[i] + M_c[i]) % m;
    }
    return x;
  }
};



```
{% endraw %}

<a href="../../index.html">Back to top page</a>

