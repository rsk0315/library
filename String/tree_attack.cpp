/**
 * @brief tree attack
 * @author えびちゃん
 * @see https://codeforces.com/blog/entry/60442
 */

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <queue>
#include <tuple>
#include <vector>

#ifdef CALL_FROM_TEST
#include "utility/literals.cpp"
#endif

std::vector<int> tree_attack(intmax_t p, intmax_t b, size_t k) {
  struct node {
    intmax_t value;
    size_t pos, neg;
    node() = default;
    node(intmax_t v, size_t l, size_t r): value(v), pos(l), neg(r) {}
    bool operator <(node const& that) const { return value < that.value; }
  };

  std::vector<std::vector<node>> cl(k+1);
  size_t n = 1_zu << k;
  cl[0].assign(n, node(1, n-1, -1_zu));
  for (size_t j = 1; j < n; ++j) {
    cl[0][j].value = __int128(cl[0][j-1].value) * b % p;
    cl[0][j].pos = n-1-j;
  }
  std::sort(cl[0].begin(), cl[0].end());

  for (size_t i = 1; i <= k; ++i) {
    cl[i].resize(n >> i);
    for (size_t j = 0; j < cl[i].size(); ++j) {
      size_t jl = j << 1 | 0;
      size_t jr = j << 1 | 1;
      if (cl[i-1][jr] < cl[i-1][jl]) {
        cl[i][j].value = cl[i-1][jl].value - cl[i-1][jr].value;
        cl[i][j].pos = jl;
        cl[i][j].neg = jr;
      } else {
        cl[i][j].value = cl[i-1][jr].value - cl[i-1][jl].value;
        cl[i][j].pos = jr;
        cl[i][j].neg = jl;
      }
    }
    std::sort(cl[i].begin(), cl[i].end());
    if (cl[i][0].value > 0) continue;

    std::vector<int> res(n, 0);
    std::queue<std::tuple<size_t, size_t, bool>> q;  // i, j, neg?
    q.emplace(i-1, cl[i][0].pos, false);
    q.emplace(i-1, cl[i][0].neg, true);
    while (!q.empty()) {
      auto [i, j, neg] = q.front();
      q.pop();
      if (i == -1_zu) {
        if (j != -1_zu) res[j] = (neg? -1: +1);
        continue;
      }
      q.emplace(i-1, cl[i][j].pos, neg);
      q.emplace(i-1, cl[i][j].neg, !neg);
    }
    return res;
  }
  return {};
}
