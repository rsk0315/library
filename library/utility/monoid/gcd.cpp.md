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


# :warning: 最大公約数を得る演算のモノイド <small>(utility/monoid/gcd.cpp)</small>

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#0991b1681f77f54af5325f2eb1ef5d3e">utility/monoid</a>
* <a href="{{ site.github.repository_url }}/blob/master/utility/monoid/gcd.cpp">View this file on GitHub</a>
    - Last commit date: 1970-01-01 00:00:00+00:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#ifndef H_gcd_monoid
#define H_gcd_monoid

/**
 * @brief 最大公約数を得る演算のモノイド
 * @author えびちゃん
 */

#include <utility>

template <typename Tp>
class gcd_monoid {
public:
  using value_type = Tp;

private:
  value_type M_x = 0;

  static constexpr value_type S_gcd(value_type x, value_type y) {
    while (y) std::swap(x %= y, y);
    return x;
  }

public:
  gcd_monoid() = default;  // identity

  gcd_monoid(value_type const& x): M_x(x) {}

  gcd_monoid& operator +=(gcd_monoid const& that) {
    M_x = S_gcd(M_x, that.M_x);
    return *this;
  }
  friend bool operator ==(gcd_monoid const& lhs, gcd_monoid const& rhs) {
    return lhs.M_x == rhs.m_x;
  }

  friend gcd_monoid operator +(gcd_monoid lhs, gcd_monoid const& rhs) { return lhs += rhs; }
  friend bool operator !=(gcd_monoid const& lhs, gcd_monoid const& rhs) {
    return !(lhs == rhs);
  }

  value_type const& get() const { return M_x; }
};

#endif  /* !defined(H_gcd_monoid) */

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "utility/monoid/gcd.cpp"



/**
 * @brief 最大公約数を得る演算のモノイド
 * @author えびちゃん
 */

#include <utility>

template <typename Tp>
class gcd_monoid {
public:
  using value_type = Tp;

private:
  value_type M_x = 0;

  static constexpr value_type S_gcd(value_type x, value_type y) {
    while (y) std::swap(x %= y, y);
    return x;
  }

public:
  gcd_monoid() = default;  // identity

  gcd_monoid(value_type const& x): M_x(x) {}

  gcd_monoid& operator +=(gcd_monoid const& that) {
    M_x = S_gcd(M_x, that.M_x);
    return *this;
  }
  friend bool operator ==(gcd_monoid const& lhs, gcd_monoid const& rhs) {
    return lhs.M_x == rhs.m_x;
  }

  friend gcd_monoid operator +(gcd_monoid lhs, gcd_monoid const& rhs) { return lhs += rhs; }
  friend bool operator !=(gcd_monoid const& lhs, gcd_monoid const& rhs) {
    return !(lhs == rhs);
  }

  value_type const& get() const { return M_x; }
};



```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

