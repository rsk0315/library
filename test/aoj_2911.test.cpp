#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2911"
#define ERROR 1e-6

#include <cstdio>
#include <cmath>
#include <utility>
#include <vector>

#include "utility/literals.cpp"
#include "Math/lp_solver.cpp"

int main() {
  size_t n;
  scanf("%zu", &n);

  std::vector<long double> x(n), y(n);
  for (size_t i = 0; i < n; ++i)
    scanf("%Lf %Lf", &x[i], &y[i]);

  std::vector d(n, std::make_pair(1e12L, -1_zu));
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < n; ++j) {
      if (i == j) continue;
      long double d0 = std::hypot(x[i]-x[j], y[i]-y[j]);
      if (d[i].first > d0) d[i] = {d0, j};
    }
  }

  std::vector<long double> c(n, 1.0L), b;
  std::vector<std::vector<long double>> a;
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < i; ++j) {
      long double d0 = std::hypot(x[i]-x[j], y[i]-y[j]);
      size_t k = a.size();
      if (d[i].first + d[j].first < d0) continue;

      a.emplace_back(n, 0.0L);
      a[k][i] = a[k][j] = 1.0L;
      b.push_back(d0);
    }
  }

  long double r = *lp_solver<long double>::maximize(a, b, c);
  long double const pi = std::acos(-1.0L);
  printf("%.20Lf\n", 2*pi*r);
}
