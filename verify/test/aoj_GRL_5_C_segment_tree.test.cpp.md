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


# :heavy_check_mark: test/aoj_GRL_5_C_segment_tree.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/aoj_GRL_5_C_segment_tree.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-06 23:03:06+09:00


* see: <a href="https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_C">https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_C</a>


## Depends on

* :question: <a href="../../library/Graph/adjacency_list.cpp.html">重みつきグラフの隣接リスト <small>(Graph/adjacency_list.cpp)</small></a>
* :heavy_check_mark: <a href="../../library/Graph/lowest_common_ancestor_segment_tree.cpp.html">最深共通祖先 (segment tree) <small>(Graph/lowest_common_ancestor_segment_tree.cpp)</small></a>
* :question: <a href="../../library/integer/bit.cpp.html">ビット演算 <small>(integer/bit.cpp)</small></a>
* :question: <a href="../../library/utility/literals.cpp.html">ユーザ定義リテラル <small>(utility/literals.cpp)</small></a>
* :heavy_check_mark: <a href="../../library/utility/stack_extend.cpp.html">スタック拡張マクロ（魔法） <small>(utility/stack_extend.cpp)</small></a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_C"

#include <cstdint>
#include <cstdio>
#include <vector>

#include "utility/stack_extend.cpp"
#include "Graph/adjacency_list.cpp"
#include "Graph/lowest_common_ancestor_segment_tree.cpp"

int main() {
  BEGIN_STACK_EXTEND(128*1024*1024);

  int n;
  scanf("%d", &n);

  adjacency_list<weighted_edge<int>, undirected_tag> g(n);
  for (size_t i = 0; i < n; ++i) {
    size_t k;
    scanf("%zu", &k);
    for (size_t j = 0; j < k; ++j) {
      size_t c;
      scanf("%zu", &c);
      g.emplace(i, c, 1);
    }
  }

  lowest_common_ancestor g_lca(g, 0);

  size_t q;
  scanf("%zu", &q);
  for (size_t i = 0; i < q; ++i) {
    size_t u, v;
    scanf("%zu %zu", &u, &v);
    printf("%zu\n", g_lca(u, v));
  }

  END_STACK_EXTEND;
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/aoj_GRL_5_C_segment_tree.test.cpp"
#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_C"

#include <cstdint>
#include <cstdio>
#include <vector>

#line 1 "utility/stack_extend.cpp"



/**
 * @brief スタック拡張マクロ（魔法）
 * @author えびちゃん
 * @see http://sigma425.hatenablog.com/entry/2016/03/26/221844
 */

#include <cstdlib>

#define BEGIN_STACK_EXTEND(size)                                        \
  void* stack_extend_memory_ = malloc(size);                            \
  void* stack_extend_origin_memory_;                                    \
  char* stack_extend_dummy_memory_ = (char*)alloca((1+(int)(((long long)stack_extend_memory_)&127))*16); \
  *stack_extend_dummy_memory_ = 0;                                      \
  asm volatile ("mov %%rsp, %%rbx\n\tmov %%rax, %%rsp":"=b"(stack_extend_origin_memory_):"a"((char*)stack_extend_memory_+(size)-1024));

#define END_STACK_EXTEND                                                \
  asm volatile ("mov %%rax, %%rsp"::"a"(stack_extend_origin_memory_));  \
  free(stack_extend_memory_);


#line 1 "Graph/adjacency_list.cpp"



/**
 * @brief 重みつきグラフの隣接リスト
 * @author えびちゃん
 */

#include <cstddef>
#include <algorithm>
#include <type_traits>
#line 13 "Graph/adjacency_list.cpp"

template <typename WeightType>
class weighted_edge {
public:
  using size_type = size_t;
  using weight_type = WeightType;

protected:
  size_type M_src, M_dst;
  weight_type M_weight;

public:
  weighted_edge() = default;
  weighted_edge(weighted_edge const&) = default;
  weighted_edge(weighted_edge&&) = default;

  weighted_edge(size_type s, size_type d, weight_type w):
    M_src(s), M_dst(d), M_weight(w)
  {}

  weighted_edge& operator =(weighted_edge const&) = default;
  weighted_edge& operator =(weighted_edge&&) = default;

  bool operator <(weighted_edge const& other) const {
    if (M_weight < other.M_weight) return true;
    if (other.M_weight < M_weight) return false;
    if (M_src != other.M_src) return M_src < other.M_src;
    return M_dst < other.M_dst;
  }

  size_type source() const { return M_src; }
  size_type target() const { return M_dst; }
  weight_type weight() const { return M_weight; }
};

struct directed_tag {};
struct undirected_tag {};

template <typename Edge, typename Directedness>
class adjacency_list {
public:
  using size_type = size_t;
  using edge_type = Edge;
  using weight_type = typename Edge::weight_type;

private:
  std::vector<std::vector<edge_type>> M_g;

public:
  adjacency_list() = default;
  adjacency_list(adjacency_list const&) = default;
  adjacency_list(adjacency_list&&) = default;
  explicit adjacency_list(size_type n): M_g(n) {}

  template <typename... Args>
  void emplace(size_type src, size_type dst, Args... args) {
    M_g[src].emplace_back(src, dst, args...);
    if (std::is_same<Directedness, undirected_tag>::value)
      M_g[dst].emplace_back(dst, src, args...);
  }

  void sort_by_index() {
    auto cmp = [](auto const& e1, auto const& e2) {
      return e1.target() < e2.target();
    };
    for (auto v: M_g) std::sort(v.begin(), v.end(), cmp);
  }

  size_type size() const { return M_g.size(); }
  auto const& operator [](size_type i) const { return M_g[i]; }
};


#line 1 "Graph/lowest_common_ancestor_segment_tree.cpp"



/**
 * @brief 最深共通祖先 (segment tree)
 * @author えびちゃん
 */

#line 11 "Graph/lowest_common_ancestor_segment_tree.cpp"
#include <tuple>
#include <utility>
#line 14 "Graph/lowest_common_ancestor_segment_tree.cpp"

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

#line 11 "utility/literals.cpp"

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


#line 10 "test/aoj_GRL_5_C_segment_tree.test.cpp"

int main() {
  BEGIN_STACK_EXTEND(128*1024*1024);

  int n;
  scanf("%d", &n);

  adjacency_list<weighted_edge<int>, undirected_tag> g(n);
  for (size_t i = 0; i < n; ++i) {
    size_t k;
    scanf("%zu", &k);
    for (size_t j = 0; j < k; ++j) {
      size_t c;
      scanf("%zu", &c);
      g.emplace(i, c, 1);
    }
  }

  lowest_common_ancestor g_lca(g, 0);

  size_t q;
  scanf("%zu", &q);
  for (size_t i = 0; i < q; ++i) {
    size_t u, v;
    scanf("%zu %zu", &u, &v);
    printf("%zu\n", g_lca(u, v));
  }

  END_STACK_EXTEND;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

