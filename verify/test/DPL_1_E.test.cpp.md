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


# :heavy_check_mark: test/DPL_1_E.test.cpp

<a href="../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/test/DPL_1_E.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-18 00:05:27+09:00


* see: <a href="https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_1_E">https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_1_E</a>


## Depends on

* :heavy_check_mark: <a href="../../library/utility/make/vector.cpp.html">多次元 vector の作成 <small>(utility/make/vector.cpp)</small></a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_1_E"

#include "../utility/make/vector.cpp"

#include <cstdio>
#include <cstdint>
#include <algorithm>
#include <string>
#include <vector>

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
#line 1 "test/DPL_1_E.test.cpp"
#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_1_E"

#line 1 "test/../utility/make/vector.cpp"
/**
 * @brief 多次元 vector の作成
 * @author えびちゃん
 */

#include <cstddef>
#include <type_traits>
#include <vector>

namespace detail {
  template <typename Tp, size_t N>
  std::vector<Tp> make_vector(
      std::vector<size_t>& sizes,
      typename std::enable_if<(N == 1), Tp const&>::type x
  ) {
    return std::vector<Tp>(sizes[0], x);
  }
  template <typename Tp, size_t N>
  auto make_vector(
      std::vector<size_t>& sizes,
      typename std::enable_if<(N > 1), Tp const&>::type x
  ) {
    size_t size = sizes[N-1];
    sizes.pop_back();
    return std::vector<decltype(make_vector<Tp, N-1>(sizes, x))>(
        size, make_vector<Tp, N-1>(sizes, x)
    );
  }
}  // detail::

template <typename Tp, size_t N>
auto make_vector(size_t const(&sizes)[N], Tp const& x = Tp()) {
  std::vector<size_t> s(N);
  for (size_t i = 0; i < N; ++i) s[i] = sizes[N-i-1];
  return detail::make_vector<Tp, N>(s, x);
}
#line 4 "test/DPL_1_E.test.cpp"

#include <cstdio>
#include <cstdint>
#include <algorithm>
#include <string>
#include <vector>

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

