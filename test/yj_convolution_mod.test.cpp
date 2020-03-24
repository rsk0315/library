#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod"

#include <cstdio>

#define CALL_FROM_TEST
#include "ModularArithmetic/modint.cpp"
#include "ModularArithmetic/polynomial.cpp"
#undef CALL_FROM_TEST

#include <cstdint>
#include <cstdio>
#include <vector>

using mi = modint<998244353>;

int main() {
  size_t n, m;
  scanf("%zu %zu", &n, &m);

  std::vector<mi> a(n), b(m);
  for (auto& ai: a) {
    int tmp;
    scanf("%d", &tmp);
    ai = tmp;
  }
  for (auto& bi: b) {
    int tmp;
    scanf("%d", &tmp);
    bi = tmp;
  }

  polynomial<mi> f(a.begin(), a.end()), g(b.begin(), b.end());
  f *= g;

  for (size_t i = 0; i+1 < n+m; ++i)
    printf("%jd%c", f[i].get(), i+2<n+m? ' ': '\n');
}
