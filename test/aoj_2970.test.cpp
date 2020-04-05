#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2970"

#include <cstdint>
#include <cstdio>
#include <vector>

#include "ModularArithmetic/chinese_remaindering.cpp"

int main() {
  size_t n;
  scanf("%zu", &n);

  std::vector<size_t> p(n), q(n);
  for (auto& pi: p) scanf("%zu", &pi), --pi;
  for (auto& qi: q) scanf("%zu", &qi), --qi;

  simultaneous_congruences sc;
  for (size_t i = 0; i < n; ++i) {
    int a = 0;
    int m = 0;
    for (size_t x = p[i], j = 0; x != i; x = q[x]) {
      ++a;
      if (j++ > n) return puts("-1"), 0;
    }
    for (size_t x = p[i], j = 0; j <= n; ++j) {
      ++m;
      x = q[x];
      if (x == p[i]) break;
      if (j == n) return puts("-1"), 0;
    }
    if (!sc.push(a, m)) return puts("-1"), 0;
  }
  printf("%jd\n", sc.get().first);
}
