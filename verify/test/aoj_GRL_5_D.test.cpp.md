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


# :x: test/aoj_GRL_5_D.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/aoj_GRL_5_D.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-26 20:17:56+09:00


* see: <a href="http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_D">http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_D</a>


## Depends on

* :question: <a href="../../library/DataStructure/basic_segment_tree.cpp.html">単一更新セグメント木 <small>(DataStructure/basic_segment_tree.cpp)</small></a>
* :question: <a href="../../library/Graph/hl_decomposition.cpp.html">HL 分解 <small>(Graph/hl_decomposition.cpp)</small></a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_D"

#include <cstdio>
#include <cassert>
#include <tuple>
#include <vector>

#include "DataStructure/basic_segment_tree.cpp"
#include "Graph/hl_decomposition.cpp"

int main() {
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
      g.set(v, w);
    } else if (t == 1) {
      size_t u;
      scanf("%zu", &u);
      int res = g.fold(u, 0);
      assert(res == g.fold(0, u));
      printf("%d\n", res);
    }
  }
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/aoj_GRL_5_D.test.cpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_D"

#include <cstdio>
#include <cassert>
#include <tuple>
#include <vector>

#line 1 "DataStructure/basic_segment_tree.cpp"



/**
 * @brief 単一更新セグメント木
 * @author えびちゃん
 */

#include <cstddef>
#include <algorithm>
#line 12 "DataStructure/basic_segment_tree.cpp"

template <typename Monoid>
class basic_segment_tree {
public:
  using value_type = Monoid;
  using size_type = size_t;

private:
  std::vector<value_type> M_c;
  size_type M_n;

public:
  basic_segment_tree() = default;

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

  void set(size_type i, value_type const& x) {
    i += M_n;
    M_c[i] = x;
    while (i > 1) {
      i >>= 1;
      M_c[i] = M_c[i<<1|0] + M_c[i<<1|1];
    }
  }

  void set(size_type i, value_type&& x) {
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
  size_type foldl_bisect(size_type l, Predicate pred) const {
    // Return minimum r such that pred(fold(l, r)) is false,
    // or -1 (of size_type) if such r does not exist.
    size_type r = M_n+M_n;
    value_type x{};
    size_type h = 0;
    if (l == M_n) return pred(x)? -1: l;
    l += M_n;
    auto bisect = [&](size_type v) -> size_type {
      while (v < M_n) {
        v <<= 1;
        if (pred(x + M_c[v])) x += M_c[v++];
      }
      return v - M_n;
    };
    for (; l < r; ++h, l >>= 1, r >>= 1) {
      if (l & 1) {
        if (!pred(x + M_c[l])) return bisect(l);
        x += M_c[l];
        ++l;
      }
      if (r & 1) --r;
    }
    while (r <<= 1, h--) {
      if (((r+1) << h) <= M_n+M_n) {
        if (!pred(x + M_c[r])) return bisect(r);
        x += M_c[r];
        ++r;
      }
    }
    return -1;
  }

  template <typename Predicate>
  size_type foldr_bisect(size_type r, Predicate pred) const {
    // Return maximum l such that pred(fold(l, r)) is false,
    // of -1 (of size_type) if such does not exist.
    size_type l = M_n;
    value_type x{};
    size_type h = 0;
    if (r == 0) return pred(x)? -1: 0;
    r += M_n;
    auto bisect = [&](size_type v) -> size_type {
      while (v < M_n) {
        v = (v << 1 | 1);
        if (pred(M_c[v] + x)) x = M_c[v--] + std::move(x);
      }
      return v - M_n;
    };
    for (; l < r; ++h, l >>= 1, r >>= 1) {
      if (l & 1) ++l;
      if (r & 1) {
        --r;
        if (!pred(M_c[r] + x)) return bisect(r);
        x = M_c[r] + std::move(x);
      }
    }
    while (l <<= 1, h--) {
      if (((l-1) << h) >= M_n) {
        --l;
        if (!pred(M_c[l] + x)) return bisect(l);
        x = M_c[l] + std::move(x);
      }
    }
    return -1;
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
#include <utility>
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

  void M_set(size_type v, value_type x, bool asc) {
    // on directed edges or on vertices
    bool dir = std::is_same<ValueAttribute, value_on_directed_edge_tag>::value;
    if (asc || !dir) M_fa.set(M_n-1 - M_in[v], x);
    if (!asc || !dir) M_fd.set(M_in[v], x);
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
  void set(size_type v, value_type x, bool asc = true) { M_set(v, x, asc); }
  template <typename Rq = RangeQuery, typename Ta = typename Rq::action_type>
  void act(size_type u, size_type v, Ta x) { M_act(u, v, x); }
};


#line 10 "test/aoj_GRL_5_D.test.cpp"

int main() {
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
      g.set(v, w);
    } else if (t == 1) {
      size_t u;
      scanf("%zu", &u);
      int res = g.fold(u, 0);
      assert(res == g.fold(0, u));
      printf("%d\n", res);
    }
  }
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

