#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0425"

#include <cstdint>
#include <cstdio>
#include <algorithm>
#include <numeric>
#include <tuple>
#include <utility>
#include <vector>

#include "algorithm/mo.cpp"

class range_function {
  size_t M_n;
  size_t M_l = 0;
  size_t M_r = 0;
  std::vector<std::pair<size_t, size_t>> M_op;
  std::vector<size_t> M_p, M_q;

  void M_swap(size_t a, size_t b) {
    std::swap(M_q[M_p[a]], M_q[M_p[b]]);
    std::swap(M_p[a], M_p[b]);
  }

public:
  range_function() = default;
  range_function(size_t n, std::vector<std::pair<size_t, size_t>> const& ab):
    M_n(n), M_op(ab), M_p(n), M_q(n)
  {
    std::iota(M_p.begin(), M_p.end(), 0);
    std::iota(M_q.begin(), M_q.end(), 0);
  }

  void push_back() { auto [a, b] = M_op[M_r++]; M_swap(a, b); }
  void push_front() { auto [a, b] = M_op[--M_l]; M_swap(M_q[a], M_q[b]); }
  void pop_back() { auto [a, b] = M_op[--M_r]; M_swap(a, b); }
  void pop_front() { auto [a, b] = M_op[M_l++]; M_swap(M_q[a], M_q[b]); }
  size_t size() const { return M_n; }

  size_t operator ()(std::pair<size_t, int> const& q) {
    auto [x, type] = q;
    return ((type == 1)? M_p[x]: M_q[x]);
  }
};

int main() {
  size_t n, k, q;
  scanf("%zu %zu %zu", &n, &k, &q);

  std::vector<std::pair<size_t, size_t>> ab(k);
  for (auto& [a, b]: ab) scanf("%zu %zu", &a, &b), --a, --b;

  using query_type = std::tuple<size_t, size_t, std::pair<size_t, int>>;
  std::vector<query_type> qs(q);
  for (auto& [s, t, p]: qs) {
    scanf("%d %zu %zu %zu", &p.second, &s, &t, &p.first);
    --s;
    --p.first;
  }

  for (auto res: mo(range_function(n, ab), qs))
    printf("%zu\n", res+1);
}
