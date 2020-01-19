/**
 * @brief 最深共通祖先 (squaring)
 * @author えびちゃん
 */


#ifdef CALL_FROM_TEST
#include "utility/literals.cpp"
#endif

#include <cstddef>
#include <algorithm>
#include <tuple>
#include <utility>
#include <vector>

class lowest_common_ancestor {
public:
  using size_type = size_t;

private:
  std::vector<size_type> M_d;
  std::vector<std::vector<size_type>> M_p;

  template <typename Tree>
  void M_dfs(Tree const& g, size_type v, size_type p) {
    for (auto const& e: g[v]) {
      size_type u = e.target();
      if (u == p) continue;
      M_p[0][u] = v;
      M_d[u] = M_d[v] + 1;
      M_dfs(g, u, v);
    }
  }

  void M_double() {
    size_type n = M_p[0].size();
    while (true) {
      bool valid = false;
      auto const& back = M_p.back();
      std::vector<size_type> tmp(n, -1);
      for (size_type i = 0; i < n; ++i) {
        if (back[i] == -1_zu) continue;
        tmp[i] = back[back[i]];
        if (tmp[i] != -1_zu) valid = true;
      }
      if (!valid) break;
      M_p.push_back(std::move(tmp));
    }
  }

public:
  lowest_common_ancestor() = default;
  lowest_common_ancestor(lowest_common_ancestor const&) = default;
  lowest_common_ancestor(lowest_common_ancestor&&) = default;

  template <typename Tree>
  lowest_common_ancestor(Tree const& g, size_type r) {
    size_type n = g.size();
    M_d.assign(n, 0);
    M_p.emplace_back(n, -1);
    M_dfs(g, r, -1);
    M_double();
  }

  lowest_common_ancestor& operator =(lowest_common_ancestor const&) = default;
  lowest_common_ancestor& operator =(lowest_common_ancestor&&) = default;

  size_type operator ()(size_type u, size_type v) const {
    if (M_d[u] > M_d[v]) std::swap(u, v);
    if (M_d[u] < M_d[v]) {
      size_type d = M_d[v] - M_d[u];
      for (size_type i = 0; i < M_p.size(); ++i)
        if (d >> i & 1) v = M_p[i][v];
    }
    if (u == v) return u;
    for (size_type i = M_p.size(); i--;) {
      if (M_p[i][u] == M_p[i][v]) continue;
      u = M_p[i][u];
      v = M_p[i][v];
    }
    return M_p[0][u];
  }
};
