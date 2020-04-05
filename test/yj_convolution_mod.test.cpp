#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod"

#include <cstdio>
#include <vector>

#include "ModularArithmetic/modint.cpp"
#include "ModularArithmetic/polynomial.cpp"

using mi = modint<998244353>;

int main() {
  size_t n, m;
  scanf("%zu %zu", &n, &m);

  std::vector<int> a(n), b(m);
  for (auto& ai: a) scanf("%d", &ai);
  for (auto& bi: b) scanf("%d", &bi);

  polynomial<mi> f(a.begin(), a.end()), g(b.begin(), b.end());
  f *= g;

  for (size_t i = 0; i+1 < n+m; ++i)
    printf("%jd%c", f[i].get(), i+2<n+m? ' ': '\n');
}
