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


# :heavy_check_mark: 区間最小値・区間加算用のヘルパークラス <small>(utility/action/add_min.cpp)</small>

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#f9ed6bc15c58239d0b090799c8486b17">utility/action</a>
* <a href="{{ site.github.repository_url }}/blob/master/utility/action/add_min.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-06 23:03:06+09:00




## Depends on

* :question: <a href="../limits.cpp.html">型依存の定数 <small>(utility/limits.cpp)</small></a>
* :question: <a href="../monoid/min.cpp.html">min を得る演算のモノイド <small>(utility/monoid/min.cpp)</small></a>


## Verified with

* :heavy_check_mark: <a href="../../../verify/test/aoj_DSL_2_H.test.cpp.html">test/aoj_DSL_2_H.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#ifndef H_action_add_min
#define H_action_add_min

/**
 * @brief 区間最小値・区間加算用のヘルパークラス
 * @author えびちゃん
 */

#include "utility/monoid/min.cpp"

template <typename Tp>
struct action_add_to_min {
  using operand_type = min_monoid<Tp>;
  using action_type = Tp;

  static void act(operand_type& op, action_type const& a) {
    op = operand_type(std::move(op).get() + a);
  }
};

#endif  /* !defined(H_action_add_min) */

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "utility/action/add_min.cpp"



/**
 * @brief 区間最小値・区間加算用のヘルパークラス
 * @author えびちゃん
 */

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

template <typename Tp>
class limits: public std::numeric_limits<Tp> {};


#line 13 "utility/monoid/min.cpp"

template <typename Tp>
class min_monoid {
public:
  using value_type = Tp;

private:
  value_type M_x = limits<value_type>::max();

public:
  min_monoid() = default;  // identity
  min_monoid(min_monoid const&) = default;
  min_monoid(min_monoid&&) = default;

  min_monoid(value_type const& x): M_x(x) {};
  min_monoid(value_type&& x): M_x(std::move(x)) {};

  min_monoid& operator =(min_monoid const&) = default;
  min_monoid& operator =(min_monoid&&) = default;

  min_monoid& operator +=(min_monoid const& that) {
    M_x = std::min(M_x, that.M_x);
    return *this;
  }
  min_monoid& operator +=(min_monoid&& that) {
    M_x = std::min(M_x, std::move(that.M_x));
    return *this;
  }

  min_monoid operator +(min_monoid const& that) const {
    return min_monoid(*this) += that;
  }
  min_monoid operator +(min_monoid&& that) const {
    return min_monoid(*this) += std::move(that);
  }

  value_type const& get() const { return M_x; }
};


#line 10 "utility/action/add_min.cpp"

template <typename Tp>
struct action_add_to_min {
  using operand_type = min_monoid<Tp>;
  using action_type = Tp;

  static void act(operand_type& op, action_type const& a) {
    op = operand_type(std::move(op).get() + a);
  }
};



```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

