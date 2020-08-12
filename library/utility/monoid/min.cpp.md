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


# :warning: min を得る演算のモノイド <small>(utility/monoid/min.cpp)</small>

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#0991b1681f77f54af5325f2eb1ef5d3e">utility/monoid</a>
* <a href="{{ site.github.repository_url }}/blob/master/utility/monoid/min.cpp">View this file on GitHub</a>
    - Last commit date: 1970-01-01 00:00:00+00:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#ifndef H_min_monoid
#define H_min_monoid

/**
 * @brief min を得る演算のモノイド
 * @author えびちゃん
 */

#include <algorithm>
#include <utility>

#include "utility/limits.cpp"

template <typename Tp>
class min_monoid {
public:
  using value_type = Tp;

private:
  value_type M_x = limits<Tp>::max();

public:
  min_monoid() = default;  // identity

  min_monoid(value_type const& x): M_x(x) {}

  min_monoid& operator +=(min_monoid const& that) {
    M_x = std::min(M_x, that.M_x);
    return *this;
  }
  friend bool operator ==(min_monoid const& lhs, min_monoid const& rhs) {
    return lhs.M_x == rhs.M_x;
  }

  friend min_monoid operator +(min_monoid lhs, min_monoid const& rhs) {
    return lhs += rhs;
  }
  friend bool operator !=(min_monoid const& lhs, min_monoid const& rhs) {
    return !(lhs == rhs);
  }

  value_type const& get() const { return M_x; }
};

#endif  /* !defined(H_min_monoid) */

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "utility/monoid/min.cpp"



/**
 * @brief min を得る演算のモノイド
 * @author えびちゃん
 */

#include <algorithm>
#include <utility>

#line 1 "utility/limits.cpp"



/**
 * @brief 型依存の定数
 * @author えびちゃん
 */

#include <limits>
#line 11 "utility/limits.cpp"

template <typename Tp>
class limits: public std::numeric_limits<Tp> {};

template <typename T1, typename T2>
class limits<std::pair<T1, T2>> {
public:
  static constexpr auto min() {
    return std::make_pair(limits<T1>::min(), limits<T2>::min());
  }
  static constexpr auto max() {
    return std::make_pair(limits<T1>::max(), limits<T2>::max());
  }
};


#line 13 "utility/monoid/min.cpp"

template <typename Tp>
class min_monoid {
public:
  using value_type = Tp;

private:
  value_type M_x = limits<Tp>::max();

public:
  min_monoid() = default;  // identity

  min_monoid(value_type const& x): M_x(x) {}

  min_monoid& operator +=(min_monoid const& that) {
    M_x = std::min(M_x, that.M_x);
    return *this;
  }
  friend bool operator ==(min_monoid const& lhs, min_monoid const& rhs) {
    return lhs.M_x == rhs.M_x;
  }

  friend min_monoid operator +(min_monoid lhs, min_monoid const& rhs) {
    return lhs += rhs;
  }
  friend bool operator !=(min_monoid const& lhs, min_monoid const& rhs) {
    return !(lhs == rhs);
  }

  value_type const& get() const { return M_x; }
};



```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

