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


# :heavy_check_mark: ラムダ式の再帰 <small>(utility/make/fix_point.cpp)</small>

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#eea2354d8759bbd52e8bbb508d91fa66">utility/make</a>
* <a href="{{ site.github.repository_url }}/blob/master/utility/make/fix_point.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-21 16:32:25+09:00




## Verified with

* :heavy_check_mark: <a href="../../../verify/test/aoj_2178.test.cpp.html">test/aoj_2178.test.cpp</a>
* :heavy_check_mark: <a href="../../../verify/test/aoj_2313.test.cpp.html">test/aoj_2313.test.cpp</a>
* :heavy_check_mark: <a href="../../../verify/test/aoj_2976.test.cpp.html">test/aoj_2976.test.cpp</a>
* :heavy_check_mark: <a href="../../../verify/test/aoj_ALDS1_10_A.test.cpp.html">test/aoj_ALDS1_10_A.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
/**
 * @brief ラムダ式の再帰
 * @author えびちゃん
 */

#ifndef H_make_fix_point
#define H_make_fix_point

#include <utility>

template <typename Fn>
class fix_point: Fn {
public:
  explicit constexpr fix_point(Fn&& f) noexcept: Fn(std::forward<Fn>(f)) {}

  template <typename... Args>
  constexpr decltype(auto) operator ()(Args&&... args) const {
    return Fn::operator ()(*this, std::forward<Args>(args)...);
  }
};

template <typename Fn>
static inline constexpr decltype(auto) make_fix_point(Fn&& f) noexcept {
  return fix_point<Fn>{std::forward<Fn>(f)};
}

#endif  /* !defined(H_make_fix_point) */

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "utility/make/fix_point.cpp"
/**
 * @brief ラムダ式の再帰
 * @author えびちゃん
 */

#ifndef H_make_fix_point
#define H_make_fix_point

#include <utility>

template <typename Fn>
class fix_point: Fn {
public:
  explicit constexpr fix_point(Fn&& f) noexcept: Fn(std::forward<Fn>(f)) {}

  template <typename... Args>
  constexpr decltype(auto) operator ()(Args&&... args) const {
    return Fn::operator ()(*this, std::forward<Args>(args)...);
  }
};

template <typename Fn>
static inline constexpr decltype(auto) make_fix_point(Fn&& f) noexcept {
  return fix_point<Fn>{std::forward<Fn>(f)};
}

#endif  /* !defined(H_make_fix_point) */

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

