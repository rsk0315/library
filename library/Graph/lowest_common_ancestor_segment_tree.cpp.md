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


# :heavy_check_mark: 最深共通祖先 (segment tree) <small>(Graph/lowest_common_ancestor_segment_tree.cpp)</small>

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#4cdbd2bafa8193091ba09509cedf94fd">Graph</a>
* <a href="{{ site.github.repository_url }}/blob/master/Graph/lowest_common_ancestor_segment_tree.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-06 23:03:06+09:00




## Depends on

* :question: <a href="../integer/bit.cpp.html">ビット演算 <small>(integer/bit.cpp)</small></a>
* :question: <a href="../utility/literals.cpp.html">ユーザ定義リテラル <small>(utility/literals.cpp)</small></a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/aoj_GRL_5_C_segment_tree.test.cpp.html">test/aoj_GRL_5_C_segment_tree.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#ifndef H_lowest_common_ancestor_segment_tree
#define H_lowest_common_ancestor_segment_tree

/**
 * @brief 最深共通祖先 (segment tree)
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
  std::vector<std::pair<size_type, size_type>> M_st;

  template <typename Tree>
  void M_euler_tour(Tree const& g, size_type v, size_type p, size_type d = 0) {
    M_e[v] = M_st.size();
    M_st.emplace_back(d, v);
    for (auto const& e: g[v]) {
      size_type u = e.target();
      if (u == p) continue;
      M_euler_tour(g, u, v, d+1);
      M_st.emplace_back(d, v);
    }
  }

  void M_build_rmq() {
    // segment tree
    size_type n = M_st.size();
    std::vector<std::pair<size_type, size_type>> tmp(n);
    M_st.insert(M_st.begin(), tmp.begin(), tmp.end());
    for (size_type i = n; i--;)
      M_st[i] = std::min(M_st[i<<1|0], M_st[i<<1|1]);
  }

public:
  lowest_common_ancestor() = default;
  lowest_common_ancestor(lowest_common_ancestor const&) = default;
  lowest_common_ancestor(lowest_common_ancestor&&) = default;

  template <typename Tree>
  lowest_common_ancestor(Tree const& g, size_type r) {
    size_type n = g.size();
    M_e.resize(n);
    M_st.reserve(n+n-2);
    M_euler_tour(g, r, -1);
    M_build_rmq();
  }

  lowest_common_ancestor& operator =(lowest_common_ancestor const&) = default;
  lowest_common_ancestor& operator =(lowest_common_ancestor&&) = default;

  size_type operator ()(size_type u, size_type v) const {
    if (u == v) return u;
    size_type l, r;
    std::tie(l, r) = std::minmax(M_e[u], M_e[v]);
    size_type n = M_st.size() >> 1;
    l += n;
    r += n+1;
    std::pair<size_type, size_type> res{n, n};
    while (l < r) {
      if (l & 1) res = std::min(res, M_st[l++]);
      if (r & 1) res = std::min(M_st[--r], res);
      l >>= 1;
      r >>= 1;
    }
    return res.second;
  }
};

#endif  /* !defined(H_lowest_common_ancestor_segment_tree) */

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "Graph/lowest_common_ancestor_segment_tree.cpp"



/**
 * @brief 最深共通祖先 (segment tree)
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

#include <climits>
#include <type_traits>

// #ifdef __has_builtin
int clz(unsigned n) { return __builtin_clz(n); }
int clz(unsigned long n) { return __builtin_clzl(n); }
int clz(unsigned long long n) { return __builtin_clzll(n); }
int ctz(unsigned n) { return __builtin_ctz(n); }
int ctz(unsigned long n) { return __builtin_ctzl(n); }
int ctz(unsigned long long n) { return __builtin_ctzll(n); }
int popcount(unsigned n) { return __builtin_popcount(n); }
int popcount(unsigned long n) { return __builtin_popcountl(n); }
int popcount(unsigned long long n) { return __builtin_popcountll(n); }
// #else
// TODO: implement
// #endif

template <typename Tp>
auto clz(Tp n) -> typename std::enable_if<std::is_signed<Tp>::value, int>::type {
  return clz(static_cast<typename std::make_unsigned<Tp>::type>(n));
}
template <typename Tp>
auto ctz(Tp n) -> typename std::enable_if<std::is_signed<Tp>::value, int>::type {
  return ctz(static_cast<typename std::make_unsigned<Tp>::type>(n));
}
template <typename Tp>
auto popcount(Tp n) -> typename std::enable_if<std::is_signed<Tp>::value, int>::type {
  return popcount(static_cast<typename std::make_unsigned<Tp>::type>(n));
}

template <typename Tp>
int parity(Tp n) { return popcount(n) & 1; }
template <typename Tp>
int ilog2(Tp n) {
  return (CHAR_BIT * sizeof(Tp) - 1) - clz(static_cast<typename std::make_unsigned<Tp>::type>(n));
}
template <typename Tp>
Tp ceil2(Tp n) {
  if (!(n & (n-1))) return n;
  return Tp(2) << ilog2(n);
}
template <typename Tp>
Tp reverse(Tp n) {
  static constexpr Tp b1 = static_cast<Tp>(0x5555555555555555);
  static constexpr Tp b2 = static_cast<Tp>(0x3333333333333333);
  static constexpr Tp b4 = static_cast<Tp>(0x0F0F0F0F0F0F0F0F);
  static constexpr Tp b8 = static_cast<Tp>(0x00FF00FF00FF00FF);
  static constexpr Tp bx = static_cast<Tp>(0x0000FFFF0000FFFF);
  n = ((n & b1) << 1) | ((n >> 1) & b1);
  n = ((n & b2) << 2) | ((n >> 2) & b2);
  n = ((n & b4) << 4) | ((n >> 4) & b4);
  n = ((n & b8) << 8) | ((n >> 8) & b8);
  n = ((n & bx) << 16) | ((n >> 16) & bx);
  if ((sizeof n) > 4) n = (n << 32) | (n >> 32);
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


#line 17 "Graph/lowest_common_ancestor_segment_tree.cpp"

class lowest_common_ancestor {
public:
  using size_type = size_t;

private:
  std::vector<size_type> M_e;
  std::vector<std::pair<size_type, size_type>> M_st;

  template <typename Tree>
  void M_euler_tour(Tree const& g, size_type v, size_type p, size_type d = 0) {
    M_e[v] = M_st.size();
    M_st.emplace_back(d, v);
    for (auto const& e: g[v]) {
      size_type u = e.target();
      if (u == p) continue;
      M_euler_tour(g, u, v, d+1);
      M_st.emplace_back(d, v);
    }
  }

  void M_build_rmq() {
    // segment tree
    size_type n = M_st.size();
    std::vector<std::pair<size_type, size_type>> tmp(n);
    M_st.insert(M_st.begin(), tmp.begin(), tmp.end());
    for (size_type i = n; i--;)
      M_st[i] = std::min(M_st[i<<1|0], M_st[i<<1|1]);
  }

public:
  lowest_common_ancestor() = default;
  lowest_common_ancestor(lowest_common_ancestor const&) = default;
  lowest_common_ancestor(lowest_common_ancestor&&) = default;

  template <typename Tree>
  lowest_common_ancestor(Tree const& g, size_type r) {
    size_type n = g.size();
    M_e.resize(n);
    M_st.reserve(n+n-2);
    M_euler_tour(g, r, -1);
    M_build_rmq();
  }

  lowest_common_ancestor& operator =(lowest_common_ancestor const&) = default;
  lowest_common_ancestor& operator =(lowest_common_ancestor&&) = default;

  size_type operator ()(size_type u, size_type v) const {
    if (u == v) return u;
    size_type l, r;
    std::tie(l, r) = std::minmax(M_e[u], M_e[v]);
    size_type n = M_st.size() >> 1;
    l += n;
    r += n+1;
    std::pair<size_type, size_type> res{n, n};
    while (l < r) {
      if (l & 1) res = std::min(res, M_st[l++]);
      if (r & 1) res = std::min(M_st[--r], res);
      l >>= 1;
      r >>= 1;
    }
    return res.second;
  }
};



```
{% endraw %}

<a href="../../index.html">Back to top page</a>

