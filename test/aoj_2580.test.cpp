#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2580"

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <utility>

#include "utility/literals.cpp"
#include "utility/make/vector.cpp"
#include "utility/make/fix_point.cpp"
#include "algorithm/monotone_minima.cpp"

int main() {
  size_t n, m, d;
  intmax_t x;
  scanf("%zu %zu %zu %jd", &n, &m, &d, &x);

  std::vector<intmax_t> p(n);
  for (auto& pi: p) scanf("%jd", &pi);

  std::vector<intmax_t> q(m);
  for (auto& qi: q) {
    intmax_t a, b;
    scanf("%jd %jd", &a, &b);
    qi = a - std::abs(b);
  }

  intmax_t const inf = 1e18;
  intmax_t res = inf;
  auto dp = make_vector({n}, inf);
  dp[0] = 0;
  for (size_t dd = 0; dd < d; ++dd) {
    std::vector<intmax_t> w(n+1, 0);
    w[0] = m;
    for (auto const& qi: q) {
      size_t i = std::upper_bound(p.begin(), p.end(), qi) - p.begin();
      --w[i];
    }
    for (size_t i = 1; i <= n; ++i) w[i] += w[i-1];

    auto tmp = make_vector({n}, inf);

    auto f = [&](size_t i, size_t j) -> intmax_t {
      if (!(j < i)) return inf;
      return dp[j] + w[j] * (p[i]-p[j]);
    };
    auto prev = monotone_minima(f, n, n);

    for (size_t i = 0; i < n; ++i)
      tmp[i] = f(i, prev[i]);

    dp = std::move(tmp);
    res = std::min(res, dp[n-1]);
    for (auto& qi: q) qi += x;
  }

  printf("%jd\n", res);
}
