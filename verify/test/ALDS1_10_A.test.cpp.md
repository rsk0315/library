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


# :heavy_check_mark: test/ALDS1_10_A.test.cpp

<a href="../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/test/ALDS1_10_A.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-19 17:22:15+09:00


* see: <a href="https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_10_A">https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_10_A</a>


## Depends on

* :heavy_check_mark: <a href="../../library/utility/make/fix_point.cpp.html">ラムダ式の再帰 <small>(utility/make/fix_point.cpp)</small></a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_10_A"

#include "utility/make/fix_point.cpp"

#include <cstdio>
#include <cstdint>
#include <vector>

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
#line 1 "test/ALDS1_10_A.test.cpp"
#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_10_A"

#line 1 "utility/make/fix_point.cpp"
/**
 * @brief ラムダ式の再帰
 * @author えびちゃん
 */

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
#line 4 "test/ALDS1_10_A.test.cpp"

#include <cstdio>
#include <cstdint>
#include <vector>

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

