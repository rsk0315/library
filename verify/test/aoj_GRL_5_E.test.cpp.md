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


# :heavy_check_mark: test/aoj_GRL_5_E.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/aoj_GRL_5_E.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-06 23:03:06+09:00


* see: <a href="https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_E">https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_E</a>


## Depends on

* :question: <a href="../../library/DataStructure/segment_tree.cpp.html">区間作用・区間和セグメント木 <small>(DataStructure/segment_tree.cpp)</small></a>
* :question: <a href="../../library/Graph/hl_decomposition.cpp.html">HL 分解 <small>(Graph/hl_decomposition.cpp)</small></a>
* :question: <a href="../../library/integer/bit.cpp.html">ビット演算 <small>(integer/bit.cpp)</small></a>
* :heavy_check_mark: <a href="../../library/utility/action/add_sum.cpp.html">区間和・区間加算用のヘルパークラス <small>(utility/action/add_sum.cpp)</small></a>
* :question: <a href="../../library/utility/monoid/length.cpp.html">和と長さを得る演算のモノイド <small>(utility/monoid/length.cpp)</small></a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_E"

#include <cstdint>
#include <cstdio>
#include <cassert>
#include <tuple>
#include <vector>

#include "utility/action/add_sum.cpp"
#include "DataStructure/segment_tree.cpp"
#include "Graph/hl_decomposition.cpp"

int main() {

  size_t n;
  scanf("%zu", &n);

  std::vector<size_t> par(n, n);
  std::vector<std::tuple<size_t, size_t, length_monoid<intmax_t>>> es;
  for (size_t i = 0; i < n; ++i) {
    size_t k;
    scanf("%zu", &k);
    for (size_t j = 0; j < k; ++j) {
      size_t c;
      scanf("%zu", &c);
      par[c] = i;
      es.emplace_back(i, c, 0);
    }
  }

  hl_decomposed_tree<segment_tree<action_add_to_sum<intmax_t>>, value_on_undirected_edge_tag> g(n, es);

  size_t q;
  scanf("%zu", &q);

  for (size_t i = 0; i < q; ++i) {
    int t;
    scanf("%d", &t);

    if (t == 0) {
      size_t v;
      intmax_t w;
      scanf("%zu %jd", &v, &w);
      g.act(v, 0, w);
    } else if (t == 1) {
      size_t u;
      scanf("%zu", &u);
      intmax_t res = g.fold(u, 0).get();
      assert(res == g.fold(0, u).get());
      printf("%jd\n", res);
    }
  }
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/aoj_GRL_5_E.test.cpp"
#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_E"

#include <cstdint>
#include <cstdio>
#include <cassert>
#include <tuple>
#include <vector>

#line 1 "utility/action/add_sum.cpp"



/**
 * @brief 区間和・区間加算用のヘルパークラス
 * @author えびちゃん
 */

#line 1 "utility/monoid/length.cpp"
/**
 * @brief 和と長さを得る演算のモノイド
 * @author えびちゃん
 */

#include <cstddef>
#include <utility>

#ifndef H_length_monoid
#define H_length_monoid

template <typename Tp>
class length_monoid {
public:
  using value_type = Tp;
  using size_type = size_t;

private:
  value_type M_x{};
  size_type M_l = 1;

public:
  length_monoid() = default;  // identity

  length_monoid(value_type const& x, size_type l = 1): M_x(x), M_l(l) {};
  length_monoid(value_type&& x, size_type l = 1): M_x(std::move(x)), M_l(l) {};

  length_monoid& operator +=(length_monoid const& that) {
    M_x += that.M_x;
    M_l += that.M_l;
    return *this;
  }
  length_monoid& operator +=(length_monoid&& that) {
    M_x += std::move(that.M_x);
    M_l += that.M_l;
    return *this;
  }

  length_monoid operator +(length_monoid const& that) const {
    return length_monoid(*this) += that;
  }
  length_monoid operator +(length_monoid&& that) const {
    return length_monoid(*this) += std::move(that);
  }

  value_type const& get() const { return M_x; }
  size_type length() const { return M_l; }
};

#endif  /* !defined(H_length_monoid) */
#line 10 "utility/action/add_sum.cpp"

template <typename Tp>
struct action_add_to_sum {
  using operand_type = length_monoid<Tp>;
  using action_type = Tp;

  static void act(operand_type& op, action_type const& a) {
    op += operand_type(a * op.length(), 0);
  }
};


#line 1 "DataStructure/segment_tree.cpp"



/**
 * @brief 区間作用・区間和セグメント木
 * @author えびちゃん
 */

#line 11 "DataStructure/segment_tree.cpp"

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


#line 13 "DataStructure/segment_tree.cpp"

template <typename Operation>
class segment_tree {
public:
  using size_type = size_t;
  using operation = Operation;
  using operand_type = typename operation::operand_type;
  using action_type = typename operation::action_type;
  using value_type = operand_type;

private:
  size_type M_n;
  std::vector<operand_type> M_c;
  std::vector<action_type> M_d;  // deferred

  void M_build(size_type i) {
    while (i > 1) {
      i >>= 1;
      M_c[i] = (M_c[i<<1|0] + M_c[i<<1|1]);
      operation::act(M_c[i], M_d[i]);
    }
  }

  void M_resolve(size_type i) {
    size_type h = ilog2(M_n) + 2;  // ilog2p1(M_n*2)
    for (size_type s = h; s > 0; --s) {
      size_type p = i >> s;
      action_type id{};
      if (M_d[p] != id) {
        M_apply(p<<1|0, M_d[p]);
        M_apply(p<<1|1, M_d[p]);
        M_d[p] = id;
      }
    }
  }

  void M_apply(size_type i, action_type const& x) {
    operation::act(M_c[i], x);
    if (i < M_n) M_d[i] += x;
  }

public:
  segment_tree() = default;
  explicit segment_tree(size_type n):
    M_n(n), M_c(n+n, operand_type{}), M_d(n, action_type{}) {}

  segment_tree(size_type n, operand_type const& x):
    M_n(n), M_c(n+n, x), M_d(n, action_type{})
  {
    for (size_type i = n; i--;) M_c[i] = M_c[i<<1|0] + M_c[i<<1|1];
  }

  template <typename InputIt>
  segment_tree(InputIt first, InputIt last): M_c(first, last) {
    M_n = M_c.size();
    M_d.assign(M_n, action_type{});
    M_c.insert(M_c.begin(), M_n, operand_type{});
    for (size_type i = M_n; i--;) M_c[i] = M_c[i<<1|0] + M_c[i<<1|1];
  }

  void assign(size_type n) {
    M_n = n;
    M_c(n+n, operand_type{});
    M_d(n, action_type{});
  }

  void assign(size_type n, operand_type const& x) {
    M_n = n;
    M_c(n+n, x);
    M_d(n, action_type{});
    for (size_type i = n; i--;) M_c[i] = M_c[i<<1|0] + M_c[i<<1|1];
  }

  template <typename InputIt>
  void assign(InputIt first, InputIt last) {
    M_c.assign(first, last);
    M_n = M_c.size();
    M_d.assign(M_n, action_type{});
    M_c.insert(M_c.begin(), M_n, operand_type{});
    for (size_type i = M_n; i--;) M_c[i] = M_c[i<<1|0] + M_c[i<<1|1];
  }

  void act(size_type l, size_type r, action_type const& x) {
    if (l == r) return;
    l += M_n;
    r += M_n;
    size_type l0 = l;
    size_type r0 = r;
    M_resolve(l0);
    M_resolve(r0-1);
    while (l < r) {
      if (l & 1) M_apply(l++, x);
      if (r & 1) M_apply(--r, x);
      l >>= 1;
      r >>= 1;
    }
    M_build(l0);
    M_build(r0-1);
  }

  operand_type fold(size_type l, size_type r) {
    operand_type resl{}, resr{};
    if (l == r) return resl;

    l += M_n;
    r += M_n;
    M_resolve(l);
    M_resolve(r-1);
    while (l < r) {
      if (l & 1) resl += M_c[l++];
      if (r & 1) resr = M_c[--r] + std::move(resr);
      l >>= 1;
      r >>= 1;
    }
    return resl += resr;
  }

  operand_type operator [](size_type i) {
    i += M_n;
    M_resolve(i);
    return M_c[i];
  }
};


#line 1 "Graph/hl_decomposition.cpp"



/**
 * @brief HL 分解
 * @author えびちゃん
 * @see https://codeforces.com/blog/entry/53170
 */

#line 11 "Graph/hl_decomposition.cpp"
#include <type_traits>
#line 14 "Graph/hl_decomposition.cpp"

struct value_on_directed_edge_tag {};
struct value_on_undirected_edge_tag {};
struct value_on_vertex_tag {};

template <typename RangeQuery, typename ValueAttribute>
class hl_decomposed_tree {
public:
  using size_type = size_t;
  using range_query_type = RangeQuery;
  using value_type = typename range_query_type::value_type;
  using attribute = ValueAttribute;

private:
  size_type M_n = 0;
  std::vector<size_type> M_p, M_hp;  // parent, heavy path root
  std::vector<size_type> M_in;
  range_query_type M_fa, M_fd;

  void M_dfs_size(
      std::vector<std::vector<size_type>>& al, std::vector<size_type>& ss,
      size_type v, size_type p
  ) {
    ss[v] = 1;
    M_p[v] = p;
    if (al[v][0] == p) std::swap(al[v][0], al[v].back());
    for (auto& u: al[v]) {
      if (u == p) continue;
      M_dfs_size(al, ss, u, v);
      ss[v] += ss[u];
      if (ss[u] > ss[al[v][0]]) std::swap(u, al[v][0]);
    }
  }

  void M_dfs_heavy_path(
      std::vector<std::vector<size_type>> const& al, std::vector<size_type> const& ss,
      size_type v, size_type& t
  ) {
    M_in[v] = t++;
    for (auto u: al[v]) {
      if (u == M_p[v]) continue;
      M_hp[u] = ((u == al[v][0])? M_hp[v]: u);
      M_dfs_heavy_path(al, ss, u, t);
    }
  }

  void M_decompose(std::vector<std::vector<size_type>>& al, size_type r = 0) {
    std::vector<size_type> ss(M_n, 0);
    M_dfs_size(al, ss, r, M_n);
    size_type in = 0;
    M_dfs_heavy_path(al, ss, r, in);
  }

  size_type M_lca(size_type u, size_type v) const {
    if (M_in[u] > M_in[v]) std::swap(u, v);
    if (M_hp[u] == M_hp[v]) return u;
    return M_lca(u, M_p[M_hp[v]]);
  }

  static void S_fold(value_type& this_, value_type that, bool foldl) {
    if (foldl) {
      this_ += that;
    } else {
      this_ = that + std::move(this_);
    }
  }

  value_type M_fold_one_way(size_type u, size_type v, bool asc) {
    value_type res{};
    if (asc) {
      while (M_hp[u] != M_hp[v]) {
        size_type l = M_n-1 - M_in[u];
        size_type r = M_n-1 - M_in[M_hp[u]];
        S_fold(res, M_fa.fold(l, r+1), true);
        u = M_p[M_hp[u]];
      }
      size_type l = M_n-1 - M_in[u];
      size_type r = M_n-1 - M_in[v];
      S_fold(res, M_fa.fold(l, r), true);
    } else {
      while (M_hp[u] != M_hp[v]) {
        size_type l = M_in[M_hp[u]];
        size_type r = M_in[u];
        S_fold(res, M_fd.fold(l, r+1), false);
        u = M_p[M_hp[u]];
      }
      size_type l = M_in[v]+1;
      size_type r = M_in[u]+1;
      S_fold(res, M_fd.fold(l, r), false);
    }
    return res;
  }

  template <typename Tp>
  void M_act_one_way(size_type u, size_type v, Tp x, bool asc) {
    if (asc) {
      while (M_hp[u] != M_hp[v]) {
        size_type l = M_n-1 - M_in[u];
        size_type r = M_n-1 - M_in[M_hp[u]];
        M_fa.act(l, r+1, x);
        u = M_p[M_hp[u]];
      }
      size_type l = M_n-1 - M_in[u];
      size_type r = M_n-1 - M_in[v];
      M_fa.act(l, r, x);
    } else {
      while (M_hp[u] != M_hp[v]) {
        size_type l = M_in[M_hp[u]];
        size_type r = M_in[u];
        M_fd.act(l, r+1, x);
        u = M_p[M_hp[u]];
      }
      size_type l = M_in[v]+1;
      size_type r = M_in[u]+1;
      M_fd.act(l, r, x);
    }
  }

  value_type M_fold(size_type u, size_type v) {
    size_type w = M_lca(u, v);
    value_type resl = M_fold_one_way(u, w, true);
    value_type resr = M_fold_one_way(v, w, false);
    if (std::is_same<attribute, value_on_vertex_tag>::value) {
      resl += M_fd.fold(M_in[w], M_in[w]+1);
    }
    return resl += resr;
  }

  void M_modify(size_type v, value_type x, bool asc) {
    // on directed edges or on vertices
    bool dir = std::is_same<ValueAttribute, value_on_directed_edge_tag>::value;
    if (asc || !dir) M_fa.modify(M_n-1 - M_in[v], x);
    if (!asc || !dir) M_fd.modify(M_in[v], x);
  }

  template <typename Tp>
  void M_act(size_type u, size_type v, Tp x) {
    size_type w = M_lca(u, v);
    M_act_one_way(u, w, x, true);
    M_act_one_way(v, w, x, false);
    if (!std::is_same<attribute, value_on_directed_edge_tag>::value) {
      M_act_one_way(v, w, x, true);
      M_act_one_way(u, w, x, false);
      if (std::is_same<attribute, value_on_vertex_tag>::value) {
        M_act_one_way(w, M_p[w], x, true);
        M_act_one_way(w, M_p[w], x, false);
      }
    }
  }

public:
  hl_decomposed_tree() = default;

  template <
    typename Va = ValueAttribute,
    typename Tp = typename std::enable_if<std::is_same<Va, value_on_vertex_tag>::value, value_type>::type
  >
  hl_decomposed_tree(
      std::vector<Tp> const& vs,
      std::vector<std::pair<size_type, size_type>> const& es, size_type r = 0
  ): M_n(vs.size()+1), M_p(M_n, M_n), M_hp(M_n, r), M_in(M_n) {
    size_type n = M_n-1;
    std::vector<std::vector<size_type>> al(M_n);
    for (auto const& [u, v]: es) {
      al[u].push_back(v);
      al[v].push_back(u);
    }
    al[r].push_back(n);
    al[n].push_back(r);
    M_decompose(al, n);

    std::vector<value_type> a(M_n), d(M_n);
    for (size_type i = 0; i < n; ++i) a[M_in[i]] = d[M_in[i]] = vs[i];
    M_fa.assign(a.rbegin(), a.rend());
    M_fd.assign(d.begin(), d.end());
  }

  template <
    typename Va = ValueAttribute,
    typename Sz = typename std::enable_if<!std::is_same<Va, value_on_vertex_tag>::value, size_type>::type
  >
  hl_decomposed_tree(
      Sz n, std::vector<std::tuple<size_type, size_type, value_type>> const& es,
      size_type r = 0
  ): M_n(n), M_p(n, n), M_hp(n, r), M_in(n) {
    std::vector<std::vector<size_type>> al(n);
    bool undir = std::is_same<Va, value_on_undirected_edge_tag>::value;
    for (auto const& [u, v, w]: es) {
      al[u].push_back(v);
      if (undir) al[v].push_back(u);
    }
    M_decompose(al);

    std::vector<value_type> a(n), d(n);
    for (auto const& [u, v, w]: es) {
      if (u == M_p[v]) {
        d[M_in[v]] = w;
        if (undir) a[M_in[v]] = w;
      } else {
        a[M_in[u]] = w;
        if (undir) d[M_in[u]] = w;
      }
    }

    M_fa.assign(a.rbegin(), a.rend());
    M_fd.assign(d.begin(), d.end());
  }

  value_type fold(size_type u, size_type v) { return M_fold(u, v); }
  void modify(size_type v, value_type x, bool asc = true) { M_modify(v, x, asc); }
  template <typename Rq = RangeQuery, typename Ta = typename Rq::action_type>
  void act(size_type u, size_type v, Ta x) { M_act(u, v, x); }
};


#line 12 "test/aoj_GRL_5_E.test.cpp"

int main() {

  size_t n;
  scanf("%zu", &n);

  std::vector<size_t> par(n, n);
  std::vector<std::tuple<size_t, size_t, length_monoid<intmax_t>>> es;
  for (size_t i = 0; i < n; ++i) {
    size_t k;
    scanf("%zu", &k);
    for (size_t j = 0; j < k; ++j) {
      size_t c;
      scanf("%zu", &c);
      par[c] = i;
      es.emplace_back(i, c, 0);
    }
  }

  hl_decomposed_tree<segment_tree<action_add_to_sum<intmax_t>>, value_on_undirected_edge_tag> g(n, es);

  size_t q;
  scanf("%zu", &q);

  for (size_t i = 0; i < q; ++i) {
    int t;
    scanf("%d", &t);

    if (t == 0) {
      size_t v;
      intmax_t w;
      scanf("%zu %jd", &v, &w);
      g.act(v, 0, w);
    } else if (t == 1) {
      size_t u;
      scanf("%zu", &u);
      intmax_t res = g.fold(u, 0).get();
      assert(res == g.fold(0, u).get());
      printf("%jd\n", res);
    }
  }
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

