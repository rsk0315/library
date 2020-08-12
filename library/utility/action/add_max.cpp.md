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


# :warning: 区間最大値・区間加算用のヘルパークラス <small>(utility/action/add_max.cpp)</small>

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#f9ed6bc15c58239d0b090799c8486b17">utility/action</a>
* <a href="{{ site.github.repository_url }}/blob/master/utility/action/add_max.cpp">View this file on GitHub</a>
    - Last commit date: 2020-07-11 14:49:45+09:00




## Depends on

* :question: <a href="../limits.cpp.html">型依存の定数 <small>(utility/limits.cpp)</small></a>
* :heavy_check_mark: <a href="../monoid/max.cpp.html">max を得る演算のモノイド <small>(utility/monoid/max.cpp)</small></a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#ifndef H_action_add_max
#define H_action_add_max

/**
 * @brief 区間最大値・区間加算用のヘルパークラス
 * @author えびちゃん
 */

#include "utility/monoid/max.cpp"

template <typename Tp>
struct action_add_to_max {
  using operand_type = max_monoid<Tp>;
  using action_type = Tp;

  static void act(operand_type& op, action_type const& a) {
    op = operand_type(std::move(op).get() + a);
  }
};

#endif  /* !defined(H_action_add_max) */

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "utility/action/add_max.cpp"



/**
 * @brief 区間最大値・区間加算用のヘルパークラス
 * @author えびちゃん
 */

#line 1 "utility/monoid/max.cpp"



/**
 * @brief max を得る演算のモノイド
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


#line 13 "utility/monoid/max.cpp"

template <typename Tp>
class max_monoid {
public:
  using value_type = Tp;

private:
  value_type M_x = limits<value_type>::min();

public:
  max_monoid() = default;  // identity
  max_monoid(max_monoid const&) = default;
  max_monoid(max_monoid&&) = default;

  max_monoid(value_type const& x): M_x(x) {};
  max_monoid(value_type&& x): M_x(std::move(x)) {};

  max_monoid& operator =(max_monoid const&) = default;
  max_monoid& operator =(max_monoid&&) = default;

  max_monoid& operator +=(max_monoid const& that) {
    M_x = std::max(M_x, that.M_x);
    return *this;
  }
  max_monoid& operator +=(max_monoid&& that) {
    M_x = std::max(M_x, std::move(that.M_x));
    return *this;
  }

  max_monoid operator +(max_monoid const& that) const {
    return max_monoid(*this) += that;
  }
  max_monoid operator +(max_monoid&& that) const {
    return max_monoid(*this) += std::move(that);
  }

  value_type const& get() const { return M_x; }
};


#line 10 "utility/action/add_max.cpp"

template <typename Tp>
struct action_add_to_max {
  using operand_type = max_monoid<Tp>;
  using action_type = Tp;

  static void act(operand_type& op, action_type const& a) {
    op = operand_type(std::move(op).get() + a);
  }
};



```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

