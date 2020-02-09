/**
 * @brief 2-SAT
 * @author えびちゃん
 */

#ifndef H_two_sat
#define H_two_sat

#ifdef CALL_FROM_TEST
#include "Graph/adjacency_list.cpp"
#include "Graph/scc.cpp"
#endif

#include <cstddef>
#include <vector>

class two_sat {
public:
  using size_type = unsigned;

private:
  size_type M_n;
  adjacency_list<weighted_edge<bool>, directed_tag> M_g;
  std::vector<size_type> M_scc;
  bool M_sat;

  void M_solve() {
    if (!M_scc.empty()) return;
    M_scc = strongly_connected_components(M_g);
    for (size_type i = 0; i < M_n; ++i)
      if (M_scc[i] == M_scc[i+M_n]) {
        M_sat = false;
        return;
      }
    M_sat = true;
  }

public:
  two_sat() = default;
  two_sat(two_sat const&) = default;
  two_sat(two_sat&&) = default;

  two_sat(size_type n): M_n(n), M_g(n+n) {}

  two_sat& operator =(two_sat const&) = default;
  two_sat& operator =(two_sat&&) = default;

  void push(size_type i, bool bi, size_type j, bool bj) {
    M_scc.clear();

    size_type not_i = i + M_n;
    size_type not_j = j + M_n;
    if (!bi) std::swap(i, not_i);
    if (!bj) std::swap(j, not_j);

    // i or j, (not i => j, not j => i)
    M_g.emplace(not_i, j, 1);
    M_g.emplace(not_j, i, 1);
  }

  bool satisfiable() {
    M_solve();
    return M_sat;    
  }

  bool operator [](size_type i) {
    M_solve();
    return M_scc[i+M_n] < M_scc[i];
  }
};

#endif  /* !defined(H_two_sat) */
