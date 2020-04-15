#define PROBLEM "https://yukicoder.me/problems/no/703"
#define IGNORE
// @ignore

#include <cstdint>
#include <cstdio>
#include <algorithm>
#include <vector>

#include "DataStructure/li_chao_tree.cpp"

int main() {
  size_t n;
  scanf("%zu", &n);

  std::vector<intmax_t> a(n), x(n), y(n);
  for (auto& ai: a) scanf("%jd", &ai);
  for (auto& xi: x) scanf("%jd", &xi);
  for (auto& yi: y) scanf("%jd", &yi);

  lower_linear_envelope<intmax_t, li_chao_tree_tag> f(a.begin(), a.end());

  std::vector<intmax_t> dp(n+1);
  dp[0] = 0;
  for (size_t i = 0; i < n; ++i) {
    f.push(-2*x[i], dp[i] + x[i]*x[i] + y[i]*y[i]);
    dp[i+1] = f.get_nth(i) + a[i]*a[i];
  }

  printf("%jd\n", dp[n]);
}
