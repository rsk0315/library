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
