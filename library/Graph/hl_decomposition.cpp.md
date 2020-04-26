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


# :question: HL 分解 <small>(Graph/hl_decomposition.cpp)</small>

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#4cdbd2bafa8193091ba09509cedf94fd">Graph</a>
* <a href="{{ site.github.repository_url }}/blob/master/Graph/hl_decomposition.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-27 02:19:10+09:00


* see: <a href="https://codeforces.com/blog/entry/53170">https://codeforces.com/blog/entry/53170</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/aoj_GRL_5_D.test.cpp.html">test/aoj_GRL_5_D.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj_GRL_5_E.test.cpp.html">test/aoj_GRL_5_E.test.cpp</a>
* :x: <a href="../../verify/test/yj_vertex_add_path_sum.test.cpp.html">test/yj_vertex_add_path_sum.test.cpp</a>
* :x: <a href="../../verify/test/yj_vertex_set_path_composite.test.cpp.html">test/yj_vertex_set_path_composite.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#ifndef H_heavy_light_decomposition
#define H_heavy_light_decomposition

/**
 * @brief HL 分解
 * @author えびちゃん
 * @see https://codeforces.com/blog/entry/53170
 */

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
    for (auto const& e: es) {
      size_type u, v;
      std::tie(u, v, std::ignore) = e;
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

#endif  /* !defined(H_heavy_light_decomposition) */

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "Graph/hl_decomposition.cpp"



/**
 * @brief HL 分解
 * @author えびちゃん
 * @see https://codeforces.com/blog/entry/53170
 */

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
    for (auto const& e: es) {
      size_type u, v;
      std::tie(u, v, std::ignore) = e;
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



```
{% endraw %}

<a href="../../index.html">Back to top page</a>

