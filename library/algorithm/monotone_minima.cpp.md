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
<script type="text/javascript" src="../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../assets/css/copy-button.css" />


# :heavy_check_mark: monotone minima <small>(algorithm/monotone_minima.cpp)</small>

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#ed469618898d75b149e5c7c4b6a1c415">algorithm</a>
* <a href="{{ site.github.repository_url }}/blob/master/algorithm/monotone_minima.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-06 04:52:14+09:00




## Depends on

* :question: <a href="../utility/make/fix_point.cpp.html">ラムダ式の再帰 <small>(utility/make/fix_point.cpp)</small></a>


## Required by

* :heavy_check_mark: <a href="online_to_offline_optimization.cpp.html">オンライン・オフライン変換 <small>(algorithm/online_to_offline_optimization.cpp)</small></a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/aoj_2580.test.cpp.html">test/aoj_2580.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yc_703_onoff.test.cpp.html">test/yc_703_onoff.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yc_704_onoff.test.cpp.html">test/yc_704_onoff.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yc_705_onoff.test.cpp.html">test/yc_705_onoff.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#ifndef H_monotone_minima
#define H_monotone_minima

/**
 * @brief monotone minima
 * @author えびちゃん
 */

#include <cstddef>
#include <utility>
#include <vector>

#include "utility/make/fix_point.cpp"

template <typename Fn>
auto monotone_minima(Fn&& f, size_t h, size_t w) {
  using value_type = decltype(f(h, w));
  std::vector<size_t> res(h);

  make_fix_point([&](auto dfs, size_t hl, size_t hu, size_t wl, size_t wu) -> void {
      if (hl >= hu) return;
      size_t hm = (hl+hu) >> 1;
      value_type min = f(hm, wl);
      res[hm] = wl;
      for (size_t j = wl+1; j < wu; ++j) {
        value_type cur = f(hm, j);
        if (cur < min) {
          min = std::move(cur);
          res[hm] = j;
        }
      }
      if (hl == hm) return;
      dfs(hl, hm, wl, res[hm]+1);
      dfs(hm+1, hu, res[hm], wu);
  })(0, h, 0, w);
  return res;
}

#endif /* !defined(H_monotone_minima) */

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "algorithm/monotone_minima.cpp"



/**
 * @brief monotone minima
 * @author えびちゃん
 */

#include <cstddef>
#include <utility>
#include <vector>

#line 1 "utility/make/fix_point.cpp"
/**
 * @brief ラムダ式の再帰
 * @author えびちゃん
 */

#ifndef H_make_fix_point
#define H_make_fix_point

#line 10 "utility/make/fix_point.cpp"

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
#line 14 "algorithm/monotone_minima.cpp"

template <typename Fn>
auto monotone_minima(Fn&& f, size_t h, size_t w) {
  using value_type = decltype(f(h, w));
  std::vector<size_t> res(h);

  make_fix_point([&](auto dfs, size_t hl, size_t hu, size_t wl, size_t wu) -> void {
      if (hl >= hu) return;
      size_t hm = (hl+hu) >> 1;
      value_type min = f(hm, wl);
      res[hm] = wl;
      for (size_t j = wl+1; j < wu; ++j) {
        value_type cur = f(hm, j);
        if (cur < min) {
          min = std::move(cur);
          res[hm] = j;
        }
      }
      if (hl == hm) return;
      dfs(hl, hm, wl, res[hm]+1);
      dfs(hm+1, hu, res[hm], wu);
  })(0, h, 0, w);
  return res;
}



```
{% endraw %}

<a href="../../index.html">Back to top page</a>

