#define IGNORE
// @ignore

/**
 * @brief HL 分解
 * @author えびちゃん
 */

#ifndef H_heavy_light_decomposition
#define H_heavy_light_decomposition

#include <cstddef>
#include <type_traits>
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
  std::vector<size_type> M_p, M_hp, M_hc;  // parent, heavy parent/child
  std::vector<size_type> M_in;
  std::vector<value_type> M_ea, M_ed;  // ascending/descending edge
  range_query_type M_fa, M_fd;  // folded

  void M_dfs_size();
  void M_dfs_build();

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

  value_type M_fold_one_way(size_type u, size_type v, bool asc);

  template <typename Tp>
  void M_act_one_way(size_type u, size_type v, Tp x, bool asc);
  // chain の途中で切れる場合とか、上まで行く場合とか、根とか、light で終わる場合とか
  // ちゃんと気をつけるべきことに気をつける

  value_type M_fold(size_type u, size_type v) {
    size_type w = M_lca(u, v);
    value_type resl = M_fold_one_way(u, w, true);
    value_type resr = M_fold_one_way(v, w, false);
    if (std::is_same<attribute, value_on_vertex_tag>::value) {
      resl += M_ea[w];
    }
    return resl += resr;
  }

  void M_modify(size_type v, value_type x) {
  }

  template <typename Tp>
  void M_act(size_type u, size_type v, Tp x) {
    size_type w = M_lca(u, v);
    M_act_one_way.act(u, w, x, true);
    M_act_one_way.act(v, w, x, false);
    if (!std::is_same<attribute, value_on_directed_edge_tag>::value) {
      M_act_one_way.act(v, w, x, true);
      M_act_one_way.act(u, w, x, false);
      if (std::is_same<attribute, value_on_vertex_tag>::value) {
        M_act_one_way(w, M_p[w], x, true);
        M_act_one_way(w, M_p[w], x, false);
      }
    }
  }

public:
  hl_decomposed_tree() = default;
  explicit hl_decomposed_tree(size_type n): M_n(n) {
    // on vertex なら ++n
  }

  // on vertex なら [first, last) で頂点属性与えてもいいか

  template <
    typename Va = ValueAttribute,
    typename std::enable_if<std::is_same<Va, value_on_vertex_tag>::value>
  >
  void push(size_type u, size_type v);

  template <
    typename Va = ValueAttribute,
    typename std::enable_if<!std::is_same<Va, value_on_vertex_tag>::value>
  >
  void push(size_type u, size_type v, value_type x);

  void decompose();

  value_type fold(size_type u, size_type v) { return M_fold(u, v); }
  void modify(size_type v, value_type x) { M_modify(v, x); }
  template <typename Tp>
  void act(size_type u, size_type v, Tp x) { M_act(u, v, x); }
};

#endif  /* !defined(H_heavy_light_decomposition) */
