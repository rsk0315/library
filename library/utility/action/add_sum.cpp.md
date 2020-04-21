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


# :heavy_check_mark: 区間和・区間加算用のヘルパークラス <small>(utility/action/add_sum.cpp)</small>

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#f9ed6bc15c58239d0b090799c8486b17">utility/action</a>
* <a href="{{ site.github.repository_url }}/blob/master/utility/action/add_sum.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-06 04:52:14+09:00




## Depends on

* :heavy_check_mark: <a href="../monoid/length.cpp.html">和と長さを得る演算のモノイド <small>(utility/monoid/length.cpp)</small></a>


## Verified with

* :heavy_check_mark: <a href="../../../verify/test/aoj_DSL_2_G.test.cpp.html">test/aoj_DSL_2_G.test.cpp</a>
* :heavy_check_mark: <a href="../../../verify/test/aoj_GRL_5_E.test.cpp.html">test/aoj_GRL_5_E.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#ifndef H_action_add_sum
#define H_action_add_sum

/**
 * @brief 区間和・区間加算用のヘルパークラス
 * @author えびちゃん
 */

#include "utility/monoid/length.cpp"

template <typename Tp>
struct action_add_to_sum {
  using operand_type = length_monoid<Tp>;
  using action_type = Tp;

  static void act(operand_type& op, action_type const& a) {
    op += operand_type(a * op.length(), 0);
  }
};

#endif  /* !defined(H_action_add_sum) */

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "utility/action/add_sum.cpp"



/**
 * @brief 区間和・区間加算用のヘルパークラス
 * @author えびちゃん
 */

#line 1 "utility/monoid/length.cpp"
/**
 * @brief 和と長さを得る演算のモノイド
 * @author えびちゃん
 */

#include <cstddef>
#include <utility>

#ifndef H_length_monoid
#define H_length_monoid

template <typename Tp>
class length_monoid {
public:
  using value_type = Tp;
  using size_type = size_t;

private:
  value_type M_x{};
  size_type M_l = 1;

public:
  length_monoid() = default;  // identity

  length_monoid(value_type const& x, size_type l = 1): M_x(x), M_l(l) {};
  length_monoid(value_type&& x, size_type l = 1): M_x(std::move(x)), M_l(l) {};

  length_monoid& operator +=(length_monoid const& that) {
    M_x += that.M_x;
    M_l += that.M_l;
    return *this;
  }
  length_monoid& operator +=(length_monoid&& that) {
    M_x += std::move(that.M_x);
    M_l += that.M_l;
    return *this;
  }

  length_monoid operator +(length_monoid const& that) const {
    return length_monoid(*this) += that;
  }
  length_monoid operator +(length_monoid&& that) const {
    return length_monoid(*this) += std::move(that);
  }

  value_type const& get() const { return M_x; }
  size_type length() const { return M_l; }
};

#endif  /* !defined(H_length_monoid) */
#line 10 "utility/action/add_sum.cpp"

template <typename Tp>
struct action_add_to_sum {
  using operand_type = length_monoid<Tp>;
  using action_type = Tp;

  static void act(operand_type& op, action_type const& a) {
    op += operand_type(a * op.length(), 0);
  }
};



```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

