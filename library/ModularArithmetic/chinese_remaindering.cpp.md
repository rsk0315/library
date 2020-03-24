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


# :warning: 連立合同式の解の構成 <small>(ModularArithmetic/chinese_remaindering.cpp)</small>

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#495e431c85de4c533fce4ff12db613fe">ModularArithmetic</a>
* <a href="{{ site.github.repository_url }}/blob/master/ModularArithmetic/chinese_remaindering.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-25 00:08:02+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
/**
 * @brief 連立合同式の解の構成
 * @author えびちゃん
 */

#ifndef H_chinese_remaindering
#define H_chinese_remaindering

#include <tuple>
#include <utility>

class simultaneous_congruences {
public:
  using value_type = intmax_t;

private:
  value_type M_mod = 1;
  value_type M_sol = 0;
  using safe_type = __int128;

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
  simultaneous_congruences() = default;

  bool push(value_type a, value_type m) {
    if (M_mod == 0) return false;

    auto [g, x, y] = S_gcd_bezout(M_mod, m);
    value_type mod = M_mod / g * m;
    value_type sol = (safe_type(M_mod) / g * a % mod * x + safe_type(m) / g * M_sol % mod * y) % mod;
    if (sol < 0) sol += mod;
    if (g > 1 && (sol % M_mod != M_sol || sol % m != a)) {
      M_mod = M_sol = 0;
      return false;
    }
    M_sol = sol;
    M_mod = mod;
    return true;
  }

  auto get() const { return std::make_pair(M_sol, M_mod); }
};

#endif  /* !defined(H_chinese_remaindering) */

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "ModularArithmetic/chinese_remaindering.cpp"
/**
 * @brief 連立合同式の解の構成
 * @author えびちゃん
 */

#ifndef H_chinese_remaindering
#define H_chinese_remaindering

#include <tuple>
#include <utility>

class simultaneous_congruences {
public:
  using value_type = intmax_t;

private:
  value_type M_mod = 1;
  value_type M_sol = 0;
  using safe_type = __int128;

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
  simultaneous_congruences() = default;

  bool push(value_type a, value_type m) {
    if (M_mod == 0) return false;

    auto [g, x, y] = S_gcd_bezout(M_mod, m);
    value_type mod = M_mod / g * m;
    value_type sol = (safe_type(M_mod) / g * a % mod * x + safe_type(m) / g * M_sol % mod * y) % mod;
    if (sol < 0) sol += mod;
    if (g > 1 && (sol % M_mod != M_sol || sol % m != a)) {
      M_mod = M_sol = 0;
      return false;
    }
    M_sol = sol;
    M_mod = mod;
    return true;
  }

  auto get() const { return std::make_pair(M_sol, M_mod); }
};

#endif  /* !defined(H_chinese_remaindering) */

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

