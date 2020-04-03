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


# :heavy_check_mark: 一次関数の合成を得る演算のモノイド <small>(utility/monoid/composite.cpp)</small>

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#0991b1681f77f54af5325f2eb1ef5d3e">utility/monoid</a>
* <a href="{{ site.github.repository_url }}/blob/master/utility/monoid/composite.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-04 02:52:37+09:00




## Verified with

* :heavy_check_mark: <a href="../../../verify/test/yj_point_set_range_composite.test.cpp.html">test/yj_point_set_range_composite.test.cpp</a>
* :heavy_check_mark: <a href="../../../verify/test/yj_queue_operate_all_composite.test.cpp.html">test/yj_queue_operate_all_composite.test.cpp</a>
* :heavy_check_mark: <a href="../../../verify/test/yj_range_affine_range_sum.test.cpp.html">test/yj_range_affine_range_sum.test.cpp</a>
* :heavy_check_mark: <a href="../../../verify/test/yj_vertex_set_path_composite.test.cpp.html">test/yj_vertex_set_path_composite.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
/**
 * @brief 一次関数の合成を得る演算のモノイド
 * @author えびちゃん
 */

#include <algorithm>
#include <utility>

#ifndef H_composite_monoid
#define H_composite_monoid

template <typename Tp>
class composite_monoid {
public:
  using value_type = Tp;

private:
  value_type M_a = 1;
  value_type M_b = 0;

public:
  composite_monoid() = default;  // identity

  composite_monoid(value_type a, value_type b): M_a(a), M_b(b) {};

  composite_monoid& operator +=(composite_monoid that) {
    M_a *= that.M_a;
    M_b *= that.M_a;
    M_b += that.M_b;
    return *this;
  }

  composite_monoid operator +(composite_monoid const& that) const {
    return composite_monoid(*this) += that;
  }
  composite_monoid operator +(composite_monoid&& that) const {
    return composite_monoid(*this) += std::move(that);
  }

  bool operator ==(composite_monoid const& that) const {
    return (M_a == that.M_a && M_b == that.M_b);
  }
  bool operator !=(composite_monoid const& that) const { return !(*this == that); }

  auto get() const { return std::make_pair(M_a, M_b); }
  value_type operator ()(value_type x) const { return M_a * x + M_b; }
};

#endif  /* !defined(H_composite_monoid) */

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "utility/monoid/composite.cpp"
/**
 * @brief 一次関数の合成を得る演算のモノイド
 * @author えびちゃん
 */

#include <algorithm>
#include <utility>

#ifndef H_composite_monoid
#define H_composite_monoid

template <typename Tp>
class composite_monoid {
public:
  using value_type = Tp;

private:
  value_type M_a = 1;
  value_type M_b = 0;

public:
  composite_monoid() = default;  // identity

  composite_monoid(value_type a, value_type b): M_a(a), M_b(b) {};

  composite_monoid& operator +=(composite_monoid that) {
    M_a *= that.M_a;
    M_b *= that.M_a;
    M_b += that.M_b;
    return *this;
  }

  composite_monoid operator +(composite_monoid const& that) const {
    return composite_monoid(*this) += that;
  }
  composite_monoid operator +(composite_monoid&& that) const {
    return composite_monoid(*this) += std::move(that);
  }

  bool operator ==(composite_monoid const& that) const {
    return (M_a == that.M_a && M_b == that.M_b);
  }
  bool operator !=(composite_monoid const& that) const { return !(*this == that); }

  auto get() const { return std::make_pair(M_a, M_b); }
  value_type operator ()(value_type x) const { return M_a * x + M_b; }
};

#endif  /* !defined(H_composite_monoid) */

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

