#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2446"
#define ERROR 1e-7

#define CALL_FROM_TEST
#include "algorithm/moebius_transform.cpp"
#include "utility/literals.cpp"
#include "integer/gcd.cpp"
#undef CALL_FROM_TEST

#include <cstdint>
#include <cstdio>
#include <vector>

bool lcm_overflow(intmax_t m, intmax_t n, intmax_t& res) {
  return __builtin_mul_overflow(m / gcd(m, n), n, &res);
}

intmax_t g(std::vector<intmax_t> const& a, size_t i, size_t m) {
  intmax_t d = 1;
  for (size_t j = 0; j < a.size(); ++j)
    if (i >> j & 1)
      if (lcm_overflow(d, a[j], d)) return 0;
  return m / d;
}

int main() {
  size_t n, m;
  scanf("%zu %zu", &n, &m);

  std::vector<intmax_t> a(n), p(n);
  for (auto& ai: a) scanf("%jd", &ai);
  for (auto& pi: p) scanf("%jd", &pi);

  std::vector<intmax_t> dp(1_zu << n, 0);
  for (size_t i = 1; i < dp.size(); ++i)
    dp[i] = g(a, i, m);

  moebius_transform(dp.begin(), dp.end());

  double res = 0;
  for (size_t i = 0; i < (1_zu << n); ++i) {
    double pi = 1;
    for (size_t j = 0; j < n; ++j)
      pi *= ((i >> j & 1)? p[j]: 100-p[j]) / 100.0;

    intmax_t vi = dp[i];
    if (!parity(i)) vi = -vi;
    res += pi * vi;
  }

  printf("%.12f\n", res);
}
