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


# :x: ロリハを衝突させるやつ (tree attack) <small>(String/tree_attack.cpp)</small>

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#27118326006d3829667a400ad23d5d98">String</a>
* <a href="{{ site.github.repository_url }}/blob/master/String/tree_attack.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-06 04:52:14+09:00


* see: <a href="https://codeforces.com/blog/entry/60442">https://codeforces.com/blog/entry/60442</a>


## Depends on

* :question: <a href="../utility/literals.cpp.html">ユーザ定義リテラル <small>(utility/literals.cpp)</small></a>


## Verified with

* :x: <a href="../../verify/test/yc_3014.test.cpp.html">test/yc_3014.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#ifndef H_tree_attack
#define H_tree_attack

/**
 * @brief ロリハを衝突させるやつ (tree attack)
 * @author えびちゃん
 * @see https://codeforces.com/blog/entry/60442
 */

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <queue>
#include <tuple>
#include <vector>

#include "utility/literals.cpp"

std::vector<int> tree_attack(intmax_t p, intmax_t b, size_t k, int sigma = 2) {
  struct node {
    intmax_t value;
    size_t pos, neg;
    int coef;
    node() = default;
    node(intmax_t v, size_t l, size_t r, int c): value(v), pos(l), neg(r), coef(c) {}
    bool operator <(node const& that) const { return value < that.value; }
  };

  std::vector<std::vector<node>> cl(k+1);
  size_t n = 1_zu << k;
  cl[0].assign(n, node(1, n-1, -1_zu, 1));
  intmax_t pow = 1;
  for (size_t j = 1; j < n; ++j) {
    pow = __int128(pow) * b % p;
    cl[0][j].value = pow;
    cl[0][j].coef = 1;
    intmax_t cur = pow;
    for (int s = 2; s < sigma; ++s) {
      cur = __int128(cur + pow) % p;
      if (cur < cl[0][j].value) {
        cl[0][j].value = cur;
        cl[0][j].coef = s;
      }
    }
    cl[0][j].pos = n-1-j;
  }

  std::sort(cl[0].begin(), cl[0].end());

  std::vector<int> coef(n);
  for (size_t i = 0; i < n; ++i)
    coef[cl[0][i].pos] = cl[0][i].coef;

  for (size_t i = 1; i <= k; ++i) {
    cl[i].resize(n >> i);
    for (size_t j = 0; j < cl[i].size(); ++j) {
      size_t jl = j << 1 | 0;
      size_t jr = j << 1 | 1;
      if (cl[i-1][jr] < cl[i-1][jl]) {
        cl[i][j].value = cl[i-1][jl].value - cl[i-1][jr].value;
        cl[i][j].pos = jl;
        cl[i][j].neg = jr;
      } else {
        cl[i][j].value = cl[i-1][jr].value - cl[i-1][jl].value;
        cl[i][j].pos = jr;
        cl[i][j].neg = jl;
      }
    }
    std::sort(cl[i].begin(), cl[i].end());
    if (cl[i][0].value > 0) continue;

    std::vector<int> res(n, 0);
    std::queue<std::tuple<size_t, size_t, bool>> q;  // i, j, neg?
    q.emplace(i-1, cl[i][0].pos, false);
    q.emplace(i-1, cl[i][0].neg, true);
    while (!q.empty()) {
      auto [i, j, neg] = q.front();
      q.pop();
      if (i == -1_zu) {
        if (j != -1_zu) res[j] = (neg? -coef[j]: +coef[j]);
        continue;
      }
      q.emplace(i-1, cl[i][j].pos, neg);
      q.emplace(i-1, cl[i][j].neg, !neg);
    }
    return res;
  }
  return {};
}

#endif  /* !defined(H_tree_attack) */

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "String/tree_attack.cpp"



/**
 * @brief ロリハを衝突させるやつ (tree attack)
 * @author えびちゃん
 * @see https://codeforces.com/blog/entry/60442
 */

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <queue>
#include <tuple>
#include <vector>

#line 1 "utility/literals.cpp"



/**
 * @brief ユーザ定義リテラル
 * @author えびちゃん
 */

#line 11 "utility/literals.cpp"

constexpr intmax_t  operator ""_jd(unsigned long long n) { return n; }
constexpr uintmax_t operator ""_ju(unsigned long long n) { return n; }
constexpr size_t    operator ""_zu(unsigned long long n) { return n; }
constexpr ptrdiff_t operator ""_td(unsigned long long n) { return n; }


#line 18 "String/tree_attack.cpp"

std::vector<int> tree_attack(intmax_t p, intmax_t b, size_t k, int sigma = 2) {
  struct node {
    intmax_t value;
    size_t pos, neg;
    int coef;
    node() = default;
    node(intmax_t v, size_t l, size_t r, int c): value(v), pos(l), neg(r), coef(c) {}
    bool operator <(node const& that) const { return value < that.value; }
  };

  std::vector<std::vector<node>> cl(k+1);
  size_t n = 1_zu << k;
  cl[0].assign(n, node(1, n-1, -1_zu, 1));
  intmax_t pow = 1;
  for (size_t j = 1; j < n; ++j) {
    pow = __int128(pow) * b % p;
    cl[0][j].value = pow;
    cl[0][j].coef = 1;
    intmax_t cur = pow;
    for (int s = 2; s < sigma; ++s) {
      cur = __int128(cur + pow) % p;
      if (cur < cl[0][j].value) {
        cl[0][j].value = cur;
        cl[0][j].coef = s;
      }
    }
    cl[0][j].pos = n-1-j;
  }

  std::sort(cl[0].begin(), cl[0].end());

  std::vector<int> coef(n);
  for (size_t i = 0; i < n; ++i)
    coef[cl[0][i].pos] = cl[0][i].coef;

  for (size_t i = 1; i <= k; ++i) {
    cl[i].resize(n >> i);
    for (size_t j = 0; j < cl[i].size(); ++j) {
      size_t jl = j << 1 | 0;
      size_t jr = j << 1 | 1;
      if (cl[i-1][jr] < cl[i-1][jl]) {
        cl[i][j].value = cl[i-1][jl].value - cl[i-1][jr].value;
        cl[i][j].pos = jl;
        cl[i][j].neg = jr;
      } else {
        cl[i][j].value = cl[i-1][jr].value - cl[i-1][jl].value;
        cl[i][j].pos = jr;
        cl[i][j].neg = jl;
      }
    }
    std::sort(cl[i].begin(), cl[i].end());
    if (cl[i][0].value > 0) continue;

    std::vector<int> res(n, 0);
    std::queue<std::tuple<size_t, size_t, bool>> q;  // i, j, neg?
    q.emplace(i-1, cl[i][0].pos, false);
    q.emplace(i-1, cl[i][0].neg, true);
    while (!q.empty()) {
      auto [i, j, neg] = q.front();
      q.pop();
      if (i == -1_zu) {
        if (j != -1_zu) res[j] = (neg? -coef[j]: +coef[j]);
        continue;
      }
      q.emplace(i-1, cl[i][j].pos, neg);
      q.emplace(i-1, cl[i][j].neg, !neg);
    }
    return res;
  }
  return {};
}



```
{% endraw %}

<a href="../../index.html">Back to top page</a>

