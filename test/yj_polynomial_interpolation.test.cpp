#define PROBLEM "https://judge.yosupo.jp/problem/polynomial_interpolation"

#include <cstdint>
#include <cstdio>
#include <algorithm>
#include <vector>

#include "ModularArithmetic/modint.cpp"
#include "ModularArithmetic/polynomial.cpp"
#include "ModularArithmetic/interpolation.cpp"

constexpr intmax_t mod = 998244353;
using mi = modint<mod>;

int main() {
  size_t n;
  scanf("%zu", &n);

  std::vector<intmax_t> x(n), y(n);
  for (auto& xi: x) scanf("%jd", &xi);
  for (auto& yi: y) scanf("%jd", &yi);

  std::vector<mi> xs(x.begin(), x.end()), ys(y.begin(), y.end());
  auto f = interpolate(xs, ys);

  for (size_t i = 0; i < n; ++i)
    printf("%d%c", f[i].get(), i+1<n? ' ': '\n');
}
