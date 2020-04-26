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


# :heavy_check_mark: 部分和の最大値を得る演算のモノイドクラス <small>(utility/monoid/max_subsum.cpp)</small>

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#0991b1681f77f54af5325f2eb1ef5d3e">utility/monoid</a>
* <a href="{{ site.github.repository_url }}/blob/master/utility/monoid/max_subsum.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-26 02:32:04+09:00




## Verified with

* :heavy_check_mark: <a href="../../../verify/test/aoj_3111.test.cpp.html">test/aoj_3111.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#ifndef H_max_subsum_monoid
#define H_max_subsum_monoid

/**
 * @brief 部分和の最大値を得る演算のモノイドクラス
 * @author えびちゃん
 */

#include <algorithm>

template <typename Tp>
class max_subsum_monoid {
public:
  using value_type = Tp;

private:
  value_type M_pre = 0, M_suf = 0, M_sub = 0, M_whole = 0;
  bool M_empty = true;

public:
  max_subsum_monoid() = default;  // identity

  max_subsum_monoid(value_type const& x):
    M_pre(x), M_suf(x), M_sub(x), M_whole(x), M_empty(false) {}

  max_subsum_monoid& operator +=(max_subsum_monoid const& that) {
    if (that.M_empty) return *this;
    if (M_empty) return (*this = that);
    M_sub = std::max({M_sub, M_suf + that.M_pre, that.M_sub});
    M_suf = std::max(M_suf + that.M_whole, that.M_suf);
    M_pre = std::max(M_pre, M_whole + that.M_pre);
    M_whole += that.M_whole;
    return *this;
  }
  friend bool operator ==(max_subsum_monoid const& lhs, max_subsum_monoid const& rhs) {
    return (
        lhs.M_pre == rhs.M_pre
        && lhs.M_suf == rhs.M_suf
        && lhs.M_sub == rhs.M_sub
        && lhs.M_whole == rhs.M_whole
    );
  }

  friend max_subsum_monoid operator +(max_subsum_monoid lhs, max_subsum_monoid const& rhs) {
    return lhs += rhs;
  }
  friend bool operator !=(max_subsum_monoid const& lhs, max_subsum_monoid const& rhs) {
    return !(lhs == rhs);
  }

  value_type const& get() const {
    return M_sub;
  }
};

#endif  /* !defined(H_max_subsum_monoid) */

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "utility/monoid/max_subsum.cpp"



/**
 * @brief 部分和の最大値を得る演算のモノイドクラス
 * @author えびちゃん
 */

#include <algorithm>

template <typename Tp>
class max_subsum_monoid {
public:
  using value_type = Tp;

private:
  value_type M_pre = 0, M_suf = 0, M_sub = 0, M_whole = 0;
  bool M_empty = true;

public:
  max_subsum_monoid() = default;  // identity

  max_subsum_monoid(value_type const& x):
    M_pre(x), M_suf(x), M_sub(x), M_whole(x), M_empty(false) {}

  max_subsum_monoid& operator +=(max_subsum_monoid const& that) {
    if (that.M_empty) return *this;
    if (M_empty) return (*this = that);
    M_sub = std::max({M_sub, M_suf + that.M_pre, that.M_sub});
    M_suf = std::max(M_suf + that.M_whole, that.M_suf);
    M_pre = std::max(M_pre, M_whole + that.M_pre);
    M_whole += that.M_whole;
    return *this;
  }
  friend bool operator ==(max_subsum_monoid const& lhs, max_subsum_monoid const& rhs) {
    return (
        lhs.M_pre == rhs.M_pre
        && lhs.M_suf == rhs.M_suf
        && lhs.M_sub == rhs.M_sub
        && lhs.M_whole == rhs.M_whole
    );
  }

  friend max_subsum_monoid operator +(max_subsum_monoid lhs, max_subsum_monoid const& rhs) {
    return lhs += rhs;
  }
  friend bool operator !=(max_subsum_monoid const& lhs, max_subsum_monoid const& rhs) {
    return !(lhs == rhs);
  }

  value_type const& get() const {
    return M_sub;
  }
};



```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

