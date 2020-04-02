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


# :heavy_check_mark: test/aoj_GRL_5_D.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/aoj_GRL_5_D.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-03 02:50:21+09:00


* see: <a href="https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_D">https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_D</a>


## Depends on

* :heavy_check_mark: <a href="../../library/DataStructure/basic_segment_tree.cpp.html">単一更新セグメント木 <small>(DataStructure/basic_segment_tree.cpp)</small></a>
* :heavy_check_mark: <a href="../../library/Graph/hl_decomposition.cpp.html">HL 分解 <small>(Graph/hl_decomposition.cpp)</small></a>
* :heavy_check_mark: <a href="../../library/utility/stack_extend.cpp.html">スタック拡張マクロ（魔法） <small>(utility/stack_extend.cpp)</small></a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_D"

#define CALL_FROM_TEST
#include "utility/stack_extend.cpp"
#include "DataStructure/basic_segment_tree.cpp"
#include "Graph/hl_decomposition.cpp"
#undef CALL_FROM_TEST

#include <cstdio>
#include <cassert>
#include <tuple>
#include <vector>

int main() {
  BEGIN_STACK_EXTEND(256*1024*1024);

  size_t n;
  scanf("%zu", &n);

  std::vector<size_t> par(n, n);
  std::vector<std::tuple<size_t, size_t, int>> es;
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

  hl_decomposed_tree<basic_segment_tree<int>, value_on_undirected_edge_tag> g(n, es);

  size_t q;
  scanf("%zu", &q);

  for (size_t i = 0; i < q; ++i) {
    int t;
    scanf("%d", &t);

    if (t == 0) {
      size_t v;
      int w;
      scanf("%zu %d", &v, &w);
      w += g.fold(v, par[v]);
      g.modify(v, w);
    } else if (t == 1) {
      size_t u;
      scanf("%zu", &u);
      int res = g.fold(u, 0);
      assert(res == g.fold(0, u));
      printf("%d\n", res);
    }
  }

  END_STACK_EXTEND;
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/aoj_GRL_5_D.test.cpp"
#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_D"

#define CALL_FROM_TEST
#line 1 "utility/stack_extend.cpp"
/**
 * @brief スタック拡張マクロ（魔法）
 * @author えびちゃん
 * @see http://sigma425.hatenablog.com/entry/2016/03/26/221844
 */

#ifndef H_stack_extend
#define H_stack_extend

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

#endif  /* !defined(H_stack_extend) */
#line 1 "DataStructure/basic_segment_tree.cpp"
/**
 * @brief 単一更新セグメント木
 * @author えびちゃん
 */

#ifndef H_basic_segment_tree
#define H_basic_segment_tree

#include <cstddef>
#include <vector>

template <typename Monoid>
class basic_segment_tree {
public:
  using value_type = Monoid;
  using size_type = size_t;

private:
  std::vector<value_type> M_c;
  size_type M_n;

  std::vector<size_type> M_covering_segments(size_type l, size_type r) const {
    std::vector<size_type> left, right;
    l += M_n;
    r += M_n;
    while (l < r) {
      if (l & 1) left.push_back(l++);
      if (r & 1) right.push_back(--r);
      l >>= 1;
      r >>= 1;
    }
    left.insert(left.end(), right.rbegin(), right.rend());
    return left;
  }

public:
  basic_segment_tree() = default;
  basic_segment_tree(basic_segment_tree const&) = default;
  basic_segment_tree(basic_segment_tree&&) = default;

  explicit basic_segment_tree(size_type n): M_c(n+n), M_n(n) {}
  explicit basic_segment_tree(size_type n, value_type const& x):
    M_c(n+n, x), M_n(n)
  {
    for (size_type i = n; i--;) M_c[i] = M_c[i<<1|0] + M_c[i<<1|1];
  }

  template <typename InputIt>
  basic_segment_tree(InputIt first, InputIt last) {
    std::vector<value_type> tmp(first, last);
    M_n = tmp.size();
    M_c.resize(M_n);
    M_c.insert(M_c.end(), tmp.begin(), tmp.end());
    for (size_type i = M_n; i--;) M_c[i] = M_c[i<<1|0] + M_c[i<<1|1];
  }

  void assign(size_type n, value_type const& x) {
    M_c.assign(n+n, x);
    M_n = n;
    for (size_type i = n; i--;) M_c[i] = M_c[i<<1|0] + M_c[i<<1|1];
  }

  template <typename InputIt>
  void assign(InputIt first, InputIt last) {
    std::vector<value_type> tmp(first, last);
    M_n = tmp.size();
    M_c.resize(M_n);
    M_c.insert(M_c.end(), tmp.begin(), tmp.end());
    for (size_type i = M_n; i--;) M_c[i] = M_c[i<<1|0] + M_c[i<<1|1];
  }

  void modify(size_type i, value_type const& x) {
    i += M_n;
    M_c[i] = x;
    while (i > 1) {
      i >>= 1;
      M_c[i] = M_c[i<<1|0] + M_c[i<<1|1];
    }
  }

  void modify(size_type i, value_type&& x) {
    i += M_n;
    M_c[i] = std::move(x);
    while (i > 1) {
      i >>= 1;
      M_c[i] = M_c[i<<1|0] + M_c[i<<1|1];
    }
  }

  value_type const& operator [](size_type i) const { return M_c[i + M_n]; }

  value_type fold(size_type l, size_type r) const {
    value_type resl{}, resr{};
    l += M_n;
    r += M_n;
    while (l < r) {
      if (l & 1) resl += M_c[l++];
      if (r & 1) resr = M_c[--r] + std::move(resr);
      l >>= 1;
      r >>= 1;
    }
    return resl += resr;
  }

  template <typename Predicate>
  size_type partition_point(size_type l, Predicate pred) const {
    if (l == M_n) return l;
    value_type x{};
    size_type v = M_n + M_n;
    std::vector<size_type> cs = M_covering_segments(l, M_n);

    // search the subroot
    for (auto s: cs) {
      if (!pred(x + M_c[s])) {
        v = s;
        break;
      }
      x += M_c[s];
    }

    // search the leaf
    while (v < M_n) {
      v <<= 1;
      if (pred(x + M_c[v])) {
        x += M_c[v];
        v |= 1;
      }
    }

    return v - M_n;
  }
};

#endif  /* !defined(H_basic_segment_tree) */
#line 1 "Graph/hl_decomposition.cpp"
/**
 * @brief HL 分解
 * @author えびちゃん
 * @see https://codeforces.com/blog/entry/53170
 * @see https://judge.yosupo.jp/problem/vertex_add_path_sum
 * @see https://judge.yosupo.jp/problem/vertex_set_path_composite
 */

#ifndef H_heavy_light_decomposition
#define H_heavy_light_decomposition

#include <cstddef>
#include <type_traits>
#include <utility>
#include <vector>

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
      resl += M_fd.fold(M_in[M_p[w]], M_in[w]);
    }
    return resl += resr;
  }

  void M_modify(size_type v, value_type x, bool asc) {
    bool undir = std::is_same<ValueAttribute, value_on_undirected_edge_tag>::value;
    if (asc || undir) M_fa.modify(M_n-1 - M_in[v], x);
    if (!asc || undir) M_fd.modify(M_in[v], x);
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
    M_decompose(al);

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

#endif  /* !defined(H_heavy_light_decomposition) */
#line 7 "test/aoj_GRL_5_D.test.cpp"
#undef CALL_FROM_TEST

#include <cstdio>
#include <cassert>
#include <tuple>
#include <vector>

int main() {
  BEGIN_STACK_EXTEND(256*1024*1024);

  size_t n;
  scanf("%zu", &n);

  std::vector<size_t> par(n, n);
  std::vector<std::tuple<size_t, size_t, int>> es;
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

  hl_decomposed_tree<basic_segment_tree<int>, value_on_undirected_edge_tag> g(n, es);

  size_t q;
  scanf("%zu", &q);

  for (size_t i = 0; i < q; ++i) {
    int t;
    scanf("%d", &t);

    if (t == 0) {
      size_t v;
      int w;
      scanf("%zu %d", &v, &w);
      w += g.fold(v, par[v]);
      g.modify(v, w);
    } else if (t == 1) {
      size_t u;
      scanf("%zu", &u);
      int res = g.fold(u, 0);
      assert(res == g.fold(0, u));
      printf("%d\n", res);
    }
  }

  END_STACK_EXTEND;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

