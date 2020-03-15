#define PROBLEM "https://yukicoder.me/problems/no/703"

#define CALL_FROM_TEST
#include "algorithm/online_to_offline_optimization.cpp"
#undef CALL_FROM_TEST

#include <cstdio>
#include <cstdint>
#include <algorithm>
#include <vector>

int main() {
  size_t n;
  scanf("%zu", &n);

  std::vector<int> a(n), x(n), y(n);
  for (auto& ai: a) scanf("%d", &ai);
  for (auto& xi: x) scanf("%d", &xi);
  for (auto& yi: y) scanf("%d", &yi);

  auto f = [&](size_t j, size_t i) {
    intmax_t dx = x[j] - a[i-1];
    intmax_t dy = y[j];
    return dx*dx + dy*dy;
  };

  auto dp = online_to_offline_optimization(f, n+1);
  printf("%jd\n", dp[n]);
}
