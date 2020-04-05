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
