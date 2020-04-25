#define PROBLEM "https://judge.yosupo.jp/problem/rectangle_sum"

#include <cstdint>
#include <cstdio>
#include <algorithm>
#include <tuple>
#include <vector>

#include "DataStructure/rectangle_query.cpp"

int main() {
  size_t n, q;
  scanf("%zu %zu", &n, &q);

  std::vector<std::tuple<int, int, intmax_t>> xyz(n);
  for (auto& [x, y, z]: xyz)
    scanf("%d %d %jd", &x, &y, &z);

  std::sort(xyz.begin(), xyz.end());
  std::vector<int> x(n), y(n);
  std::vector<intmax_t> z(n);
  for (size_t i = 0; i < n; ++i)
    std::tie(x[i], y[i], z[i]) = xyz[i];

  rectangle_query<30, intmax_t> rq(y.begin(), y.end(), z.begin(), z.end());

  for (size_t i = 0; i < q; ++i) {
    int l, d, r, u;
    scanf("%d %d %d %d", &l, &d, &r, &u);
    size_t il = std::lower_bound(x.begin(), x.end(), l) - x.begin();
    size_t ir = std::lower_bound(x.begin(), x.end(), r) - x.begin();
    intmax_t res = rq.sum_within(il, ir, d, u-1);
    printf("%jd\n", res);
  }
}
