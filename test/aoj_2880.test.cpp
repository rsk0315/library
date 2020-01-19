#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2880"

#define CALL_FROM_TEST
#include "DataStructure/integral_intervals.cpp"
#undef CALL_FROM_TEST

#include <cstdint>
#include <cstdio>
#include <algorithm>
#include <tuple>
#include <vector>

int main() {
  size_t n, m, q;
  scanf("%zu %zu %zu", &n, &m, &q);

  using query_type = std::tuple<int, int, int, int, size_t>;
  std::vector<query_type> qs;
  qs.reserve(m+q);

  for (size_t i = 0; i < m; ++i) {
    int d, a, b;
    scanf("%d %d %d", &d, &a, &b);
    qs.emplace_back(d, 1, a, b, -1);
  }

  for (size_t i = 0; i < q; ++i) {
    int e, s, t;
    scanf("%d %d %d", &e, &s, &t);
    qs.emplace_back(e, 0, s, t, i);
  }

  std::sort(qs.begin(), qs.end());

  std::vector<bool> res(q, false);
  integral_intervals<intmax_t> ii;
  for (auto const& qi: qs) {
    int d, com, s, t;
    size_t i;
    std::tie(d, com, s, t, i) = qi;

    if (com == 0) {
      if (s >= t || t <= ii.range(s).second) res[i] = true;
    } else if (com == 1) {
      ii.insert(s, t);
    }
  }

  for (auto ri: res) puts(ri? "Yes": "No");
}
