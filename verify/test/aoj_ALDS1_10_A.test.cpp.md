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


# :heavy_check_mark: test/aoj_ALDS1_10_A.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/aoj_ALDS1_10_A.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-07 01:37:10+09:00


* see: <a href="http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_10_A">http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_10_A</a>


## Depends on

* :question: <a href="../../library/utility/make/fix_point.cpp.html">ラムダ式の再帰 <small>(utility/make/fix_point.cpp)</small></a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_10_A"

#include <cstdint>
#include <cstdio>
#include <vector>

#include "utility/make/fix_point.cpp"

int main() {
  int n;
  scanf("%d", &n);

  std::vector<intmax_t> memo(n+1);
  memo[0] = memo[1] = 1;
  make_fix_point([&](auto f, int i) {
      intmax_t& res = memo[i];
      if (res > 0) return res;
      res = f(i-1) + f(i-2);
      return res;
  })(n);
  printf("%jd\n", memo[n]);
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/aoj_ALDS1_10_A.test.cpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_10_A"

#include <cstdint>
#include <cstdio>
#include <vector>

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
#line 8 "test/aoj_ALDS1_10_A.test.cpp"

int main() {
  int n;
  scanf("%d", &n);

  std::vector<intmax_t> memo(n+1);
  memo[0] = memo[1] = 1;
  make_fix_point([&](auto f, int i) {
      intmax_t& res = memo[i];
      if (res > 0) return res;
      res = f(i-1) + f(i-2);
      return res;
  })(n);
  printf("%jd\n", memo[n]);
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

