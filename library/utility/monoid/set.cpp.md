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


# :heavy_check_mark: モノイドクラス <small>(utility/monoid/set.cpp)</small>

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#0991b1681f77f54af5325f2eb1ef5d3e">utility/monoid</a>
* <a href="{{ site.github.repository_url }}/blob/master/utility/monoid/set.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-27 02:33:44+09:00




## Required by

* :heavy_check_mark: <a href="../action/set_sum.cpp.html">区間和・区間代入用のヘルパークラス <small>(utility/action/set_sum.cpp)</small></a>


## Verified with

* :heavy_check_mark: <a href="../../../verify/test/aoj_DSL_2_I.test.cpp.html">test/aoj_DSL_2_I.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#ifndef H_set_monoid
#define H_set_monoid

/**
 * @brief モノイドクラス
 * @author えびちゃん
 */

template <typename Tp>
class set_monoid {
public:
  using value_type = Tp;

private:
  bool M_empty = true;
  value_type M_x;

public:
  set_monoid() = default;  // identity

  set_monoid(value_type const& x): M_empty(false), M_x(x) {}

  set_monoid& operator +=(set_monoid const& that) {
    M_empty = that.M_empty;
    if (!that.M_empty) M_x = that.M_x;
    return *this;
  }
  friend bool operator ==(set_monoid const& lhs, set_monoid const& rhs) {
    if (lhs.M_empty && rhs.M_empty) return true;
    if (lhs.M_empty != rhs.M_empty) return false;
    return lhs.M_x == rhs.M_x;
  }

  friend set_monoid operator +(set_monoid lhs, set_monoid const& rhs) { return lhs += rhs; }
  friend bool operator !=(set_monoid const& lhs, set_monoid const& rhs) {
    return !(lhs == rhs);
  }

  bool empty() const noexcept { return M_empty; }
  value_type const& get() const { return M_x; }
};

#endif  /* !defined(H_set_monoid) */

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "utility/monoid/set.cpp"



/**
 * @brief モノイドクラス
 * @author えびちゃん
 */

template <typename Tp>
class set_monoid {
public:
  using value_type = Tp;

private:
  bool M_empty = true;
  value_type M_x;

public:
  set_monoid() = default;  // identity

  set_monoid(value_type const& x): M_empty(false), M_x(x) {}

  set_monoid& operator +=(set_monoid const& that) {
    M_empty = that.M_empty;
    if (!that.M_empty) M_x = that.M_x;
    return *this;
  }
  friend bool operator ==(set_monoid const& lhs, set_monoid const& rhs) {
    if (lhs.M_empty && rhs.M_empty) return true;
    if (lhs.M_empty != rhs.M_empty) return false;
    return lhs.M_x == rhs.M_x;
  }

  friend set_monoid operator +(set_monoid lhs, set_monoid const& rhs) { return lhs += rhs; }
  friend bool operator !=(set_monoid const& lhs, set_monoid const& rhs) {
    return !(lhs == rhs);
  }

  bool empty() const noexcept { return M_empty; }
  value_type const& get() const { return M_x; }
};



```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

