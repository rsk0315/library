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


# :heavy_check_mark: Mo's algorithm <small>(algorithm/mo.cpp)</small>

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#ed469618898d75b149e5c7c4b6a1c415">algorithm</a>
* <a href="{{ site.github.repository_url }}/blob/master/algorithm/mo.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-06 23:03:06+09:00




## Depends on

* :question: <a href="../integer/sqrt.cpp.html">整数の平方根 <small>(integer/sqrt.cpp)</small></a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/aoj_0425.test.cpp.html">test/aoj_0425.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#ifndef H_mo_algo
#define H_mo_algo

/**
 * @brief Mo's algorithm
 * @author えびちゃん
 */

#include <algorithm>
#include <numeric>
#include <tuple>
#include <utility>
#include <vector>

#include "integer/sqrt.cpp"

template <typename Rf, typename Args>
auto mo(Rf&& rf, std::vector<std::tuple<size_t, size_t, Args>> const& qs)
  -> std::vector<decltype(rf(std::declval<Args>()))>
{
  if (qs.empty()) return {};
  using value_type = decltype(rf(std::declval<Args>()));
  size_t n = rf.size();
  size_t q = qs.size();
  std::vector<value_type> res(q);
  size_t b = n / isqrt(q);
  std::vector<size_t> is(q);
  std::iota(is.begin(), is.end(), 0);
  std::sort(is.begin(), is.end(), [&](size_t i0, size_t i1) {
    size_t l0 = std::get<0>(qs[i0]) / b;
    size_t r0 = std::get<1>(qs[i0]);
    size_t l1 = std::get<0>(qs[i1]) / b;
    size_t r1 = std::get<1>(qs[i1]);
    if (l0 != l1) return l0 < l1;
    if (r0 != r1) return r0 < r1;
    return false;
  });

  size_t l = 0;
  size_t r = 0;
  for (auto i: is) {
    auto const& [l0, r0, x] = qs[i];
    while (r < r0) rf.push_back(), ++r;
    while (l > l0) rf.push_front(), --l;
    while (l < l0) rf.pop_front(), ++l;
    while (r > r0) rf.pop_back(), --r;
    res[i] = rf(x);
    l = l0;
    r = r0;
  }
  return res;
}

#endif  /* !defined(H_mo_algo) */

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "algorithm/mo.cpp"



/**
 * @brief Mo's algorithm
 * @author えびちゃん
 */

#include <algorithm>
#include <numeric>
#include <tuple>
#include <utility>
#include <vector>

#line 1 "integer/sqrt.cpp"



/**
 * @brief 整数の平方根
 * @author えびちゃん
 */

#include <climits>

template <typename Tp>
Tp isqrt(Tp n) {
  if (n <= 1) return n;
  Tp lb = 1;
  Tp ub = static_cast<Tp>(1) << (CHAR_BIT * (sizeof(Tp) / 2));
  while (ub-lb > 1) {
    Tp mid = (lb+ub) >> 1;
    ((mid*mid <= n)? lb: ub) = mid;
  }
  return lb;
}


#line 16 "algorithm/mo.cpp"

template <typename Rf, typename Args>
auto mo(Rf&& rf, std::vector<std::tuple<size_t, size_t, Args>> const& qs)
  -> std::vector<decltype(rf(std::declval<Args>()))>
{
  if (qs.empty()) return {};
  using value_type = decltype(rf(std::declval<Args>()));
  size_t n = rf.size();
  size_t q = qs.size();
  std::vector<value_type> res(q);
  size_t b = n / isqrt(q);
  std::vector<size_t> is(q);
  std::iota(is.begin(), is.end(), 0);
  std::sort(is.begin(), is.end(), [&](size_t i0, size_t i1) {
    size_t l0 = std::get<0>(qs[i0]) / b;
    size_t r0 = std::get<1>(qs[i0]);
    size_t l1 = std::get<0>(qs[i1]) / b;
    size_t r1 = std::get<1>(qs[i1]);
    if (l0 != l1) return l0 < l1;
    if (r0 != r1) return r0 < r1;
    return false;
  });

  size_t l = 0;
  size_t r = 0;
  for (auto i: is) {
    auto const& [l0, r0, x] = qs[i];
    while (r < r0) rf.push_back(), ++r;
    while (l > l0) rf.push_front(), --l;
    while (l < l0) rf.pop_front(), ++l;
    while (r > r0) rf.pop_back(), --r;
    res[i] = rf(x);
    l = l0;
    r = r0;
  }
  return res;
}



```
{% endraw %}

<a href="../../index.html">Back to top page</a>

