#define PROBLEM "https://judge.yosupo.jp/problem/log_of_formal_power_series"

#include <cstdio>
#include <algorithm>

#include "ModularArithmetic/modint.cpp"
#include "ModularArithmetic/polynomial.cpp"
#include "ModularArithmetic/operations.cpp"

using mi = modint<998244353>;

int main() {
  size_t n;
  scanf("%zu", &n);

  std::vector<int> a(n);
  for (auto& ai: a) scanf("%d", &ai);

  polynomial<mi> f(a.begin(), a.end());
  polynomial<mi> g = log(f);
  for (size_t i = 0; i < n; ++i)
    printf("%jd%c", g[i].get(), i+1<n? ' ': '\n');
}
