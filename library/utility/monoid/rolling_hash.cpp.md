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


# :heavy_check_mark: ロリハの演算のモノイド <small>(utility/monoid/rolling_hash.cpp)</small>

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#0991b1681f77f54af5325f2eb1ef5d3e">utility/monoid</a>
* <a href="{{ site.github.repository_url }}/blob/master/utility/monoid/rolling_hash.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-19 19:24:42+09:00




## Verified with

* :heavy_check_mark: <a href="../../../verify/test/aoj_2444.test.cpp.html">test/aoj_2444.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#ifndef H_rolling_hash_monoid
#define H_rolling_hash_monoid

/**
 * @brief ロリハの演算のモノイド
 * @author えびちゃん
 */

#include <utility>

template <typename ModInt>
class rolling_hash_monoid {
public:
  using value_type = ModInt;

private:
  value_type M_x = 0, M_p = 1;

public:
  rolling_hash_monoid() = default;  // identity

  rolling_hash_monoid(value_type const& x, value_type const& p): M_x(x), M_p(p) {};

  rolling_hash_monoid& operator +=(rolling_hash_monoid const& that) {
    M_x = M_x * that.M_p + that.M_x;
    M_p *= that.M_p;
    return *this;
  }

  rolling_hash_monoid operator +(rolling_hash_monoid const& that) const {
    return rolling_hash_monoid(*this) += that;
  }

  value_type const& get() const { return M_x; }
};

#endif  /* !defined(H_rolling_hash_monoid) */

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "utility/monoid/rolling_hash.cpp"



/**
 * @brief ロリハの演算のモノイド
 * @author えびちゃん
 */

#include <utility>

template <typename ModInt>
class rolling_hash_monoid {
public:
  using value_type = ModInt;

private:
  value_type M_x = 0, M_p = 1;

public:
  rolling_hash_monoid() = default;  // identity

  rolling_hash_monoid(value_type const& x, value_type const& p): M_x(x), M_p(p) {};

  rolling_hash_monoid& operator +=(rolling_hash_monoid const& that) {
    M_x = M_x * that.M_p + that.M_x;
    M_p *= that.M_p;
    return *this;
  }

  rolling_hash_monoid operator +(rolling_hash_monoid const& that) const {
    return rolling_hash_monoid(*this) += that;
  }

  value_type const& get() const { return M_x; }
};



```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

