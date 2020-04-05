#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_5_L"

#include <cstdio>
#include <vector>

#include "ModularArithmetic/modint.cpp"

using mi = modint<1000'000'007>;

int main() {
  size_t n, k;
  scanf("%zu %zu", &n, &k);

  if (n < k) return puts("0"), 0;

  std::vector<mi> dp(n+1, 0);
  dp[0] = 1;
  for (size_t i = 1; i <= k; ++i)
    for (size_t j = i; j <= n; ++j)
      dp[j] += dp[j-i];

  printf("%jd\n", dp[n-k].get());
}
