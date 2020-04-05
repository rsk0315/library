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


# :heavy_check_mark: test/aoj_DPL_1_E.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/aoj_DPL_1_E.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-06 05:07:20+09:00


* see: <a href="https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_1_E">https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_1_E</a>


## Depends on

* :heavy_check_mark: <a href="../../library/utility/make/vector.cpp.html">多次元 vector の作成 <small>(utility/make/vector.cpp)</small></a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_1_E"

#include <cstdint>
#include <cstdio>
#include <algorithm>
#include <string>
#include <vector>

#include "utility/make/vector.cpp"

int main() {
  char buf[1024];
  scanf("%s", buf);
  std::string s = buf;
  scanf("%s", buf);
  std::string t = buf;

  size_t n = s.length();
  size_t m = t.length();
  auto dp = make_vector<int>({n+1, m+1}, 0);
  for (size_t i = 1; i <= n; ++i) dp[i][0] = i;
  for (size_t j = 1; j <= m; ++j) dp[0][j] = j;

  for (size_t i = 1; i <= n; ++i)
    for (size_t j = 1; j <= m; ++j) {
      dp[i][j] = std::min({dp[i-1][j]+1,
                           dp[i][j-1]+1,
                           dp[i-1][j-1] + ((s[i-1] == t[j-1])? 0: 1)});
    }

  printf("%d\n", dp[n][m]);
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/aoj_DPL_1_E.test.cpp"
#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_1_E"

#include <cstdint>
#include <cstdio>
#include <algorithm>
#include <string>
#include <vector>

#line 1 "utility/make/vector.cpp"
/**
 * @brief 多次元 vector の作成
 * @author えびちゃん
 */

#ifndef H_make_vector
#define H_make_vector

#include <cstddef>
#include <type_traits>
#line 12 "utility/make/vector.cpp"

namespace detail {
  template <typename Tp, size_t Nb>
  auto make_vector(std::vector<size_t>& sizes, Tp const& x) {
    if constexpr (Nb == 1) {
      return std::vector(sizes[0], x);
    } else {
      size_t size = sizes[Nb-1];
      sizes.pop_back();
      return std::vector(size, make_vector<Tp, Nb-1>(sizes, x));
    }
  }
}  // detail::

template <typename Tp, size_t Nb>
auto make_vector(size_t const(&sizes)[Nb], Tp const& x = Tp()) {
  std::vector<size_t> s(Nb);
  for (size_t i = 0; i < Nb; ++i) s[i] = sizes[Nb-i-1];
  return detail::make_vector<Tp, Nb>(s, x);
}

#endif  /* !defined(H_make_vector) */
#line 10 "test/aoj_DPL_1_E.test.cpp"

int main() {
  char buf[1024];
  scanf("%s", buf);
  std::string s = buf;
  scanf("%s", buf);
  std::string t = buf;

  size_t n = s.length();
  size_t m = t.length();
  auto dp = make_vector<int>({n+1, m+1}, 0);
  for (size_t i = 1; i <= n; ++i) dp[i][0] = i;
  for (size_t j = 1; j <= m; ++j) dp[0][j] = j;

  for (size_t i = 1; i <= n; ++i)
    for (size_t j = 1; j <= m; ++j) {
      dp[i][j] = std::min({dp[i-1][j]+1,
                           dp[i][j-1]+1,
                           dp[i-1][j-1] + ((s[i-1] == t[j-1])? 0: 1)});
    }

  printf("%d\n", dp[n][m]);
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

