#ifndef H_dp_on_tree
#define H_dp_on_tree

/**
 * @brief 木 DP
 * @author えびちゃん
 */

#include <cstddef>
#include <utility>
#include <vector>

#include "utility/make/fix_point.cpp"

template <typename Monoid, typename AdjacencyList, typename Fn>
std::vector<Monoid> dp_on_tree(AdjacencyList const& g, Fn f, Monoid e = Monoid{}) {
  size_t n = g.size();
  std::vector<size_t> par(n, n);
  std::vector<std::vector<Monoid>> dpl(n), dpr(n);
  std::vector<Monoid> dp(n);
  for (size_t i = 0; i < n; ++i) {
    dpl[i].resize(g[i].size()+1, e);
    dpr[i].resize(g[i].size()+1, e);
  }

  make_fix_point([&](auto& dfs, size_t v, size_t p) -> Monoid {
    Monoid res = e;
    typename AdjacencyList::weight_type w{};
    for (size_t i = 0; i < g[v].size(); ++i) {
      auto const& e = g[v][i];
      size_t u = e.target();
      if (u == p) {
        par[v] = i;
        w = e.weight();
        continue;
      }
      Monoid tmp = dfs(u, v);
      res += tmp;
      dpl[v][i+1] = dpr[v][i] = tmp;
    }
    return f(res, w);
  })(0, n);

  make_fix_point([&](auto& dfs, size_t v, size_t p, size_t pi) -> void {
    if (p != n) {
      Monoid tmp = f(dpl[p][pi] + dpr[p][pi+1], g[p][pi].weight());
      dpl[v][par[v]+1] = dpr[v][par[v]] = tmp;
    }
    for (size_t i = 1; i < dpl[v].size(); ++i)
      dpl[v][i] = dpl[v][i-1] + std::move(dpl[v][i]);
    for (size_t i = dpr[v].size()-1; i--;)
      dpr[v][i] += dpr[v][i+1];

    dp[v] = dpr[v][0];
    for (size_t i = 0; i < g[v].size(); ++i){
      size_t u = g[v][i].target();
      if (u != p) dfs(u, v, i);
    }
  })(0, n, n);

  return dp;
}

#endif  /* !defined(H_dp_on_tree) */
