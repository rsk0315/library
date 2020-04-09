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


# :heavy_check_mark: 最深共通祖先 (sparse table) <small>(Graph/lowest_common_ancestor_sparse_table.cpp)</small>

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#4cdbd2bafa8193091ba09509cedf94fd">Graph</a>
* <a href="{{ site.github.repository_url }}/blob/master/Graph/lowest_common_ancestor_sparse_table.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-10 05:36:19+09:00




## Depends on

* :question: <a href="../integer/bit.cpp.html">ビット演算 <small>(integer/bit.cpp)</small></a>
* :heavy_check_mark: <a href="../utility/literals.cpp.html">ユーザ定義リテラル <small>(utility/literals.cpp)</small></a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/aoj_GRL_5_C_sparse_table.test.cpp.html">test/aoj_GRL_5_C_sparse_table.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#ifndef H_lowest_common_ancestor_sparse_table
#define H_lowest_common_ancestor_sparse_table

/**
 * @brief 最深共通祖先 (sparse table)
 * @author えびちゃん
 */

#include <cstddef>
#include <algorithm>
#include <tuple>
#include <utility>
#include <vector>

#include "integer/bit.cpp"
#include "utility/literals.cpp"

class lowest_common_ancestor {
public:
  using size_type = size_t;

private:
  std::vector<size_type> M_e;
  std::vector<std::vector<std::pair<size_type, size_type>>> M_st;

  template <typename Tree>
  void M_euler_tour(Tree const& g, size_type v, size_type p, size_type d = 0) {
    M_e[v] = M_st[0].size();
    M_st[0].emplace_back(d, v);
    for (auto const& e: g[v]) {
      size_type u = e.target();
      if (u == p) continue;
      M_euler_tour(g, u, v, d+1);
      M_st[0].emplace_back(d, v);
    }
  }

  void M_build_rmq() {
    // non-disjoint sparse table
    for (size_type i = 1, ii = 1; M_st[i-1].size() > ii; (++i, ii <<= 1)) {
      M_st.emplace_back();
      M_st[i].reserve(M_st[i-1].size()-ii);
      for (size_type j = ii; j < M_st[i-1].size(); ++j)
        M_st[i].push_back(std::min(M_st[i-1][j], M_st[i-1][j-ii]));
    }
  }

public:
  lowest_common_ancestor() = default;
  lowest_common_ancestor(lowest_common_ancestor const&) = default;
  lowest_common_ancestor(lowest_common_ancestor&&) = default;

  template <typename Tree>
  lowest_common_ancestor(Tree const& g, size_type r) {
    size_type n = g.size();
    M_e.resize(n);
    M_st.emplace_back();
    M_st[0].reserve(2*n);
    M_euler_tour(g, r, -1);
    M_build_rmq();
  }

  lowest_common_ancestor& operator =(lowest_common_ancestor const&) = default;
  lowest_common_ancestor& operator =(lowest_common_ancestor&&) = default;

  size_type operator ()(size_type u, size_type v) const {
    if (u == v) return u;
    size_type l, r;
    std::tie(l, r) = std::minmax(M_e[u], M_e[v]);
    size_type e = ilog2(++r-l);
    r -= 1_zu << e;
    return std::min(M_st[e][l], M_st[e][r]).second;
  }
};

#endif  /* !defined(H_lowest_common_ancestor_sparse_table) */

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "Graph/lowest_common_ancestor_sparse_table.cpp"



/**
 * @brief 最深共通祖先 (sparse table)
 * @author えびちゃん
 */

#include <cstddef>
#include <algorithm>
#include <tuple>
#include <utility>
#include <vector>

#line 1 "integer/bit.cpp"



/** 
 * @brief ビット演算
 * @author えびちゃん
 */

// XXX integral promotion 関連の注意をあまりしていません

#include <climits>
#include <type_traits>

template <typename Tp>
constexpr auto countl_zero(Tp n)
  -> typename std::enable_if<std::is_unsigned<Tp>::value, int>::type
{
  using value_type = typename std::make_unsigned<Tp>::type;
  int bits = (sizeof(value_type) * CHAR_BIT);
  if (n == 0) return bits;
  int res = 0;
  for (int i = bits / 2; i > 0; i /= 2) {
    value_type mask = ((static_cast<value_type>(1) << i) - 1) << i;
    if (n & mask) n >>= i;
    else res += i;
  }
  return res;
}
template <typename Tp>
constexpr auto countl_one(Tp n)
  -> typename std::enable_if<std::is_unsigned<Tp>::value, int>::type
{
  using value_type = typename std::make_unsigned<Tp>::type;
  return countl_zero(static_cast<value_type>(~n));
}

template <typename Tp>
constexpr auto countr_zero(Tp n)
  -> typename std::enable_if<std::is_unsigned<Tp>::value, int>::type
{
  using value_type = typename std::make_unsigned<Tp>::type;
  int bits = (sizeof(value_type) * CHAR_BIT);
  if (n == 0) return bits;
  int res = 0;
  for (int i = bits / 2; i > 0; i /= 2) {
    value_type mask = ((static_cast<value_type>(1) << i) - 1);
    if (!(n & mask)) res += i, n >>= i;
  }
  return res;
}
template <typename Tp>
constexpr auto countr_one(Tp n)
  -> typename std::enable_if<std::is_unsigned<Tp>::value, int>::type
{
  using value_type = typename std::make_unsigned<Tp>::type;
  return countr_zero(static_cast<value_type>(~n));
}

constexpr unsigned long long half_mask[] = {
  0x5555555555555555uLL, 0x3333333333333333uLL, 0x0F0F0F0F0F0F0F0FuLL,
  0x00FF00FF00FF00FFuLL, 0x0000FFFF0000FFFFuLL, 0x00000000FFFFFFFFuLL
};

template <typename Tp>
constexpr auto popcount(Tp n)
  -> typename std::enable_if<std::is_unsigned<Tp>::value, int>::type
{
  int bits = static_cast<int>((sizeof n) * CHAR_BIT);
  for (int i = 0, j = 1; j < bits; ++i, j *= 2) {
    if (j <= 8) n = (n & half_mask[i]) + ((n >> j) & half_mask[i]);
    else n += n >> j;
  }
  return n & 0xFF;
}

template <typename Tp>
constexpr auto parity(Tp n)
  -> typename std::enable_if<std::is_unsigned<Tp>::value, int>::type
{ return popcount(n) & 1; }


template <typename Tp>
int clz(Tp n) { return countl_zero(static_cast<typename std::make_unsigned<Tp>::type>(n)); }
template <typename Tp>
int ctz(Tp n) { return countr_zero(static_cast<typename std::make_unsigned<Tp>::type>(n)); }

template <typename Tp>
int ilog2(Tp n) {
  return (CHAR_BIT * sizeof(Tp) - 1) - clz(static_cast<typename std::make_unsigned<Tp>::type>(n));
}
template <typename Tp>
bool is_pow2(Tp n) { return (n > 0) && ((n & (n-1)) == 0); }
template <typename Tp>
Tp floor2(Tp n) { return is_pow2(n)? n: static_cast<Tp>(1) << ilog2(n); }
template <typename Tp>
Tp ceil2(Tp n) { return is_pow2(n)? n: static_cast<Tp>(2) << ilog2(n); }

template <typename Tp>
constexpr auto reverse(Tp n)
  -> typename std::enable_if<std::is_unsigned<Tp>::value, Tp>::type
{
  int bits = static_cast<int>((sizeof n) * CHAR_BIT);
  for (int i = 0, j = 1; j < bits; ++i, j *= 2) {
    n = ((n & half_mask[i]) << j) | ((n >> j) & half_mask[i]);
  }
  return n;
}


#line 1 "utility/literals.cpp"



/**
 * @brief ユーザ定義リテラル
 * @author えびちゃん
 */

#line 10 "utility/literals.cpp"
#include <cstdint>

constexpr intmax_t  operator ""_jd(unsigned long long n) { return n; }
constexpr uintmax_t operator ""_ju(unsigned long long n) { return n; }
constexpr size_t    operator ""_zu(unsigned long long n) { return n; }
constexpr ptrdiff_t operator ""_td(unsigned long long n) { return n; }


#line 17 "Graph/lowest_common_ancestor_sparse_table.cpp"

class lowest_common_ancestor {
public:
  using size_type = size_t;

private:
  std::vector<size_type> M_e;
  std::vector<std::vector<std::pair<size_type, size_type>>> M_st;

  template <typename Tree>
  void M_euler_tour(Tree const& g, size_type v, size_type p, size_type d = 0) {
    M_e[v] = M_st[0].size();
    M_st[0].emplace_back(d, v);
    for (auto const& e: g[v]) {
      size_type u = e.target();
      if (u == p) continue;
      M_euler_tour(g, u, v, d+1);
      M_st[0].emplace_back(d, v);
    }
  }

  void M_build_rmq() {
    // non-disjoint sparse table
    for (size_type i = 1, ii = 1; M_st[i-1].size() > ii; (++i, ii <<= 1)) {
      M_st.emplace_back();
      M_st[i].reserve(M_st[i-1].size()-ii);
      for (size_type j = ii; j < M_st[i-1].size(); ++j)
        M_st[i].push_back(std::min(M_st[i-1][j], M_st[i-1][j-ii]));
    }
  }

public:
  lowest_common_ancestor() = default;
  lowest_common_ancestor(lowest_common_ancestor const&) = default;
  lowest_common_ancestor(lowest_common_ancestor&&) = default;

  template <typename Tree>
  lowest_common_ancestor(Tree const& g, size_type r) {
    size_type n = g.size();
    M_e.resize(n);
    M_st.emplace_back();
    M_st[0].reserve(2*n);
    M_euler_tour(g, r, -1);
    M_build_rmq();
  }

  lowest_common_ancestor& operator =(lowest_common_ancestor const&) = default;
  lowest_common_ancestor& operator =(lowest_common_ancestor&&) = default;

  size_type operator ()(size_type u, size_type v) const {
    if (u == v) return u;
    size_type l, r;
    std::tie(l, r) = std::minmax(M_e[u], M_e[v]);
    size_type e = ilog2(++r-l);
    r -= 1_zu << e;
    return std::min(M_st[e][l], M_st[e][r]).second;
  }
};



```
{% endraw %}

<a href="../../index.html">Back to top page</a>

